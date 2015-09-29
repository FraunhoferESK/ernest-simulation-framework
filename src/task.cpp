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
#include <ernest/simulator.hpp>
#include <ernest/scheduler.hpp>
#include <ernest/software_function.hpp>
#include <ernest/ernest_addition.hpp>
#include <ernest/time.hpp>

namespace ERNEST
{

Task::Task(const char* instname) :
	m_ecu(nullptr),
	m_priority(0),
	m_deadline(0),
	m_current_state(SUSPENDED),
	m_scheduler(nullptr),
	m_execution_interface(nullptr),
	m_alarm(nullptr)
{
    m_move_task_state = false;
}

Task::~Task()
{
    if (m_execution_interface != nullptr) {
        delete m_execution_interface;
    }
}

TaskState Task::Execute(Time& max_runtime)
{
    list<SoftwareFunction*>::iterator it;

	// If we start executing the task, we pull all ports
	if (m_current_runtime == milliseconds(0)) {
		for (it = m_software_functions.begin(); it != m_software_functions.end(); it++) {
			(*it)->PullPorts();
		}
	}

	if (m_current_runtime + max_runtime <= m_max_runtime) {
		Simulator::Wait(max_runtime);
		m_current_runtime += max_runtime;
		m_total_runtime += max_runtime;
	} else {
		Time delta = m_max_runtime - m_current_runtime;
		Simulator::Wait(delta);

		for (it = m_software_functions.begin(); it != m_software_functions.end(); it++) {
			(*it)->Exec();
			(*it)->PushPorts();
		}

		m_current_runtime = 0;
		m_total_runtime += delta;
	}

	return SUSPENDED;
}

Time Task::RemainingExecutionTime()
{
	return m_max_runtime - m_current_runtime;
}

void Task::AddSwf(SoftwareFunction* swf)
{
    m_software_functions.push_front(swf);
    swf->SetTask(this);
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

Time Task::GetAbsoluteDeadline()
{
    return m_absolute_deadline;
}

void Task::SetAbsoluteDeadline(Time activation_time, int deadline)
{
    m_deadline = deadline;
    m_task_activation_time = activation_time;
    m_absolute_deadline = Time(m_task_activation_time.GetMilliseconds()
                               + m_deadline, Milliseconds);
}

void Task::SetTaskActivationTime(Time activation_time)
{
    m_task_activation_time = activation_time;
    m_absolute_deadline = Time(m_task_activation_time.GetMilliseconds()
                               + m_deadline, Milliseconds);
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
