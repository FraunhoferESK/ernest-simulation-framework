/* Copyright (C) 2014 Fraunhofer Institute for Embedded Systems and
 * Communication Technologies ESK
 *
 * This file is part of ERNEST.
 * 
 * ERNEST is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * ERNEST is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with ERNEST.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef ERNEST_OSEK_OS_HEADER
#define ERNEST_OSEK_OS_HEADER

#include "ernest_addition.hpp"
#include "service.hpp"
#include "task.hpp"
#include "scheduler.hpp"
#include "worst_case_execution_specification.hpp"
#include "alarm.hpp"
#include "signal.hpp"
#include "can_bus_interface.hpp"
#include "time.hpp"


namespace ERNEST
{
class CommunicationManager;
class RuntimeEnvironment;
class ExecutionSpecificationInterface;
struct Alarm;

/**
 * Data structure with information about a task's context.
 */
struct TaskContext {
    OsekOS* os;
    Task*   task;
    Alarm*  alarm;
};

/**
 * OsekOS simulation module for ERNEST Framework.
 */
class OsekOS : public Service
{
public:
    /**
     * Constructor OSEK with taking ECU as a parameter.
     *
     * @param ecu ECU this OsekOS instance runs on.
     */
    OsekOS(Ecu* ecu);

    /**
     * Destructor. Frees internal memory allocations.
     */
    ~OsekOS();

    /**
     * Update the os, e.g. update communication manager and run the
     * scheduler.
     */
    void Update();

    /**
     * Declare an alarm.
     *
     * @param start Time of the alarm in ms.
     * @param cycle Cycle/Period of the alarm in ms.
     * @param task  Task of the alarm.
     */
    void DeclareAlarm(Time start, Time cycle, Task* task);

    /**
     * Declare an alarm.
     *
     * @param start Time of the alarm in ms.
     * @param cycle Cycle/Period of the alarm in ms.
     * @param task  Task of the alarm.
     */
    void DeclareAlarm(double start, double cycle, Task* task);

    RuntimeEnvironment* GetRuntimeEnvironment();
    CommunicationManager* GetCommunicationManager();
    Timer* GetTimer();

    /**
     * Setting of the scheduler type.
     *
     * @tparam SchedulingPolicy denotes the type of scheduler used.
     */
    template <typename SchedulingPolicy>
    SchedulingPolicy* SetScheduler()
    {
    	SchedulingPolicy* scheduler;

        if (m_scheduler != nullptr) {
            delete m_scheduler;
        }

        scheduler = new SchedulingPolicy();
        m_scheduler = scheduler;

        return scheduler;
    }

    /**
     * Overloading OSEK API DeclareTask.
     *
     * The function enables the user to give variant execution time.
     *
     * @param priority Priority value of Task is set to an integer.
     * @param start Start Time of the task in ms.
     * @param cycle Cycle/Period of the task occurrence in ms.
     * @param execution_specification Pointer to execution
     *        specification of the task including execution
     *        time. Pointer will be deleted upon destruction of the
     *        task
     *
     * @tparam SwfType The type of the software function.
     */
    template<class SwfType>
    Task* DeclareTask(int priority,
                      Time start,
                      Time cycle,
                      ExecutionSpecificationInterface* execution_specification)
    {
        TaskContext* context = new TaskContext();
        context->os = this;
        context->task = m_scheduler->CreateTask(priority, start, cycle,
                                                execution_specification);

        m_timer->SetRelAlarm(m_scheduler, (int) context->task, start, cycle);

        SwfType* swf = new SwfType(context);
        context->task->AddSwf(swf);

        return context->task;
    }

    /**
     * Reception of raw data sent to OS.
     *
     * @param signalId represents the id of the corresponding Signal.
     * @param length represents the data length.
     */
    void ReceiveSignalRaw(SignalId signal_id, void* data, size_t length);

    /**
     * Assigning routing table for CAN bus.
     *
     * @param signalId represents the id of the corresponding Signal.
     * @param canId represents the id of the CAN port.
     */
    void SetCanRoutingTable(SignalId signalId, CanId canId);

    /**
     * Function Signal Task  for starting a Task.
     *
     * @param task Pointer to Task.
     */
    void SignalTask(Task* task);

private:
    /**
     * Disable copy constructor
     */
    OsekOS(const OsekOS&);

    /**
     * Disable copy assignment operator
     */
    OsekOS& operator=(const OsekOS&);

    Scheduler* m_scheduler;
    Timer* m_timer;
    RuntimeEnvironment* m_rte;
    CommunicationManager* m_com;
};

} // namespace ERNEST

#endif /* ERNEST_OSEK_OS_HEADER */
