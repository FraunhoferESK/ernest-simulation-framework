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
#ifndef ERNEST_TASK_HEADER
#define ERNEST_TASK_HEADER

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include <list>
#include "ernest_systemc.hpp"
#include "execution_specification_interface.hpp"
#include "alarm.hpp"
#include "alarm_listener.hpp"

namespace ERNEST
{
using namespace std;

class Scheduler;
class SoftwareFunction;
struct Ecu;

/**
 * Enumeration of a tasks possible states.
 */
enum TaskState {
    /**
     * The state of the task is Running
     */
    RUNNING,

    /**
     * The state of the task is Suspended
     */
    SUSPENDED,

    /**
     * The state of the task is Ready of execution
     */
    READY,

    /**
     * The state of the task is Waiting for other task to execute
     */
    WAITING
};

class Task : public sc_module, public AlarmListener
{

public:
    SC_HAS_PROCESS(Task);
    sc_event start;
    sc_mutex state_lock;
    Task(sc_module_name instname);
    ~Task();

    /**
     * Create a new Software Function.
     *
     * @param swf a pointer to a software function.
     */
    void AddSwf(SoftwareFunction* swf);

    /**
     * Removing Software Function.
     *
     * @param swf a pointer to a software function.
     */
    void RemoveSwf(SoftwareFunction* swf);

    /**
     * The priority of this tasks.
     *
     * If used by a scheduler to determine order of tasks, tasks with
     * higher priority should be preferred.
     *
     * @return the priority of this task
     */
    int GetPriority() const;

    /**
     * Reassign this tasks priority.
     *
     * @param priority new priority of this task.
     */
    void SetPriority(int priority);

    /**
     * The (relative) deadline of this task.
     *
     * The duration from task activation until absolute deadline.
     *
     * @return deadline time in ms.
     */
    int GetDeadline() const;

    /**
     * Set the deadline of this task.
     *
     * @param deadline time in ms for task execution.
     */
    void SetDeadline(int deadline);

    /**
     * The absolute deadline of this task.
     *
     * The point in time when this task must have completed execution.
     *
     * @return absolute deadline of this task.
     */
    sc_time GetAbsoluteDeadline();

    /**
     * Set the absolute deadline of this task.
     *
     * @param activation_time when this task was activated
     * @param deadline time in ms for task execution.
     */
    void SetAbsoluteDeadline(sc_time activation_time, int deadline);

    /**
     * Set the activation time of this task.
     *
     * @param activation_time absolute time when this task was activated.
     */

    void SetTaskActivationTime(sc_time activation_time);

    /**
     * Set the state of this task.
     *
     * @param state the new state of this task.
     */
    void SetState(TaskState state);

    /**
     * The task's main loop.
     *
     * Execute associated software functions, pull and push their
     * ports.
     */
    void Execute();

    /**
     * Preempt this task
     */
    void Preempt();

    /**
     * Set this task ready, if it was in waiting state.
     */
    void Release();

    /**
     * This tasks state.
     *
     * @return The current state of this task
     */
    TaskState GetTaskState();

    /**
     * Halt simulation until notification.
     */
    void SimulationWait();

    /**
     * Resume simulation.
     */
    void SimulationNotify();

    /**
     * Implementation for \ref AlarmListener.
     */
    void Notify();

    bool operator<(const Task & other) const;

    /**
     * List of software functions associated with this task.
     *
     * @return Pointer to first software function in the list.
     */
    SoftwareFunction* GetSwf();

    /**
     * Associate this task with a scheduler.
     *
     * @param scheduler the scheduler this task belongs to.
     */
    void SetScheduler(Scheduler* scheduler);

    /**
     * The associated scheduler.
     *
     * @return The associated scheduler.
     */
    Scheduler* GetScheduler();

    /**
     * Method for providing various execution details.
     *
     * @param execution_specificaton Execution specification of this task.
     */
    void SetExecutionSpecification(ExecutionSpecificationInterface* execution_specificaton);

    /**
     * Sets the ECU on which the task runs
     *
     * @param ecu Reference to the ECU on which the task runs
     */
    void SetEcu(Ecu* ecu);

    /**
     * Gets the ECU on which the task runs
     *
     * @return ECU on which the task runs
     */
    Ecu* GetEcu();

    /**
     * Sets the state to indicate if a running task is moved from current ECU
     *
     * @param move_task_state Is true if the running task is moved from current ECU
     */
    void SetMoveTaskState(bool move_task_state);

    /**
     * Gets the move task state
     *
     *@ return The move task state
     */
    bool GetMoveTaskState();

    /**
     * Sets Alarm of the task
     *
     * @param alarm Is the alarm of the task
     */
    void SetAlarm(Alarm* alarm);

    /**
     * Gets the alarm of the task
     *
     *@ return The alarm of the task
     */
    Alarm* GetAlarm();

private:
    /**
     * Disable copy constructor
     */
    Task(const Task&);

    /**
     * Disable copy assignment operator
     */
    Task& operator=(const Task&);

    void Wait();

    list<SoftwareFunction*> m_software_functions;
    Ecu* m_ecu;
    int m_priority;
    int m_deadline;
    sc_time m_absolute_deadline;
    sc_time m_task_activation_time;
    sc_time m_task_execution_time;
    TaskState m_current_state;
    Scheduler* m_scheduler;
    sc_process_handle m_process_handle;
    ExecutionSpecificationInterface* m_execution_interface;
    bool m_move_task_state;
    Alarm* m_alarm;
};

/**
 * Compare two task's priorities.
 *
 * @param lhs the first task
 * @param rhs the other task
 * @return true, if the first task has a lower priority than the other
 *         false, otherwise
 */
bool TaskCompare(const Task* lhs, const Task* rhs);

} // namespace ERNEST

#endif /* ERNEST_TASK_HEADER */
