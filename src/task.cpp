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
#include <ernest/task.hpp>
#include <ernest/scheduler.hpp>
#include <ernest/software_function.hpp>
#include <ernest/ernest_addition.hpp>
#include <ernest/time.hpp>

namespace ERNEST
{

Task::Task(sc_module_name instname) :
    sc_module(instname),
	m_ecu(nullptr),
	m_priority(0),
	m_deadline(0),
	m_current_state(SUSPENDED),
	m_scheduler(nullptr),
	m_execution_interface(nullptr),
	m_alarm(nullptr)
{
    m_move_task_state = false;
    SC_THREAD(Execute);
    m_process_handle = sc_get_current_process_handle();
    sensitive << start;
}

Task::~Task()
{
    if (m_execution_interface != nullptr) {
        delete m_execution_interface;
    }
}

void Task::Execute()
{
    list<SoftwareFunction*>::iterator it;

    wait(start);
    while (true) {
        assert(m_current_state == RUNNING);
        for(it = m_software_functions.begin(); it != m_software_functions.end(); it++) {
            (*it)->PullPorts();
            (*it)->Exec();
            wait(sc_time(m_execution_interface->GetExecutionTime().GetMilliseconds(), SC_MS));
            (*it)->PushPorts();
        }
        m_scheduler->TerminateTask(this);
    }
}

void Task::SetState(TaskState state)
{
    switch (state) {
    case READY:
        m_current_state = READY;
        break;
    case SUSPENDED:
        assert(m_current_state == RUNNING);
        m_current_state = SUSPENDED;
        break;
    case RUNNING:
        assert(m_current_state == READY);
        m_current_state = RUNNING;
        break;
    case WAITING:
        assert(m_current_state == RUNNING);
        m_current_state = WAITING;
        break;
    default:
        assert(false);
    }
}

void Task::SimulationWait()
{
    wait(start);
}

void Task::SimulationNotify()
{
    start.notify();
}

void Task::Preempt()
{
    assert(false);
    assert(m_current_state == RUNNING);
    m_current_state = READY;

    // Schedule Tasks
    m_scheduler->Schedule();

    wait(start);
}

void Task::Wait()
{
    assert(m_current_state == RUNNING);
    m_current_state = WAITING;

    // Schedule Tasks
    m_scheduler->Schedule();

    wait(start);
}

void Task::Release()
{
    assert(m_current_state == WAITING);
    m_current_state = READY;
}

TaskState Task::GetTaskState()
{
    return m_current_state;
}

void Task::AddSwf(SoftwareFunction* swf)
{
    m_software_functions.push_front(swf);
    swf->SetTask(this);
}

void Task::SetScheduler(Scheduler* scheduler)
{
    m_scheduler = scheduler;
}

Scheduler* Task::GetScheduler()
{
    return m_scheduler;
}

SoftwareFunction* Task::GetSwf()
{
    return m_software_functions.front();
}

int Task::GetPriority() const
{
    return m_priority;
}

void Task::SetPriority(int priority)
{
    m_priority = priority;
}

int Task::GetDeadline() const
{
    return m_deadline;
}

void Task::SetDeadline(int deadline)
{
    m_deadline = deadline;
}

sc_time Task::GetAbsoluteDeadline()
{
    return m_absolute_deadline;
}

void Task::SetAbsoluteDeadline(sc_time activation_time, int deadline)
{
    m_deadline = deadline;
    m_task_activation_time = activation_time;
    m_absolute_deadline = sc_time((m_task_activation_time.to_double()
                                   + m_deadline), SC_MS);
}

void Task::SetTaskActivationTime(sc_time activation_time)
{
    m_task_activation_time = activation_time;
    m_absolute_deadline = sc_time((m_task_activation_time.to_double()
                                   + m_deadline), SC_MS);
}

void Task::Notify() 
{
    m_scheduler->SignalTask(this);
}

bool Task::operator<(const Task& other) const
{
    return m_priority < other.m_priority;
}

bool TaskCompare(const Task* lhs, const Task* rhs)
{
    return lhs->GetPriority() < rhs->GetPriority();
}

void Task::SetExecutionSpecification(ExecutionSpecificationInterface* execution_specificaton)
{
    m_execution_interface = execution_specificaton;
}

void Task::SetEcu(Ecu* ecu)
{
    m_ecu = ecu;
}

Ecu* Task::GetEcu()
{
    return m_ecu;
}

void Task::SetMoveTaskState(bool move_task_state)
{
    m_move_task_state = move_task_state;
}

bool Task::GetMoveTaskState()
{
    return m_move_task_state;
}

void Task::SetAlarm(Alarm* alarm)
{
    m_alarm = alarm;
}

Alarm* Task::GetAlarm()
{
    return m_alarm;
}

} // namespace ERNEST
