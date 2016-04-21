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
#include <ernest/ernest_systemc.hpp>
#include <ernest/simulator.hpp>
#include <ernest/task.hpp>
#include <ernest/round_robin.hpp>
#include <ernest/ernest_addition.hpp>
#include <ernest/osek_os.hpp>
#include <algorithm>

namespace ERNEST
{

RoundRobin::RoundRobin() :  m_ready_task_list(TaskCompare), m_running_task(nullptr)
{
}

IOsekService* RoundRobin::Create()
{
    return new RoundRobin();
}

void RoundRobin::Update(OsekOS* osekos)
{
	Time execution_budget = Simulator::GetTimeResolution();

	if (m_running_task == nullptr) {
		StartReadyTask();
	}

	if (m_running_task != nullptr) {
		if (m_running_task->Execute(execution_budget) == SUSPENDED) {
			WaitRunningTask();
			StartReadyTask();
		}
	} else {
		Simulator::Wait(execution_budget);
	}
}

/**
 * Puts the currently running task into the wait queue
 */
void RoundRobin::WaitRunningTask()
{
	m_waiting_task_list.push_back(m_running_task);
	m_running_task = nullptr;
}

void RoundRobin::SignalTask(Task* task)
{
	// TODO
}

void RoundRobin::ActivateTask(Task* task)
{
    if (task == m_running_task) {
    	// An already running task keeps running
    	return;
    }

    // If the task is not already ready
    if (m_ready_task_list.find(task) == m_ready_task_list.end()) {
    	m_suspended_task_list.remove(task);
    	m_ready_task_list.insert(task);
    }
}

void RoundRobin::TerminateTask(Task* task)
{
	// If the task is not already suspended
	if (std::find(m_suspended_task_list.begin(), m_suspended_task_list.end(), task) == m_suspended_task_list.end()) {
		if (m_running_task == task) {
			m_running_task = nullptr;
		}

		m_waiting_task_list.remove(task);
		m_ready_task_list.erase(task);

		m_suspended_task_list.push_back(task);
	}
}

void RoundRobin::StartReadyTask()
{
	if (m_ready_task_list.empty()) {
		m_running_task = nullptr;
	} else {
		m_running_task = *(m_ready_task_list.begin());
		m_ready_task_list.erase(m_running_task);
	}
}

Task* RoundRobin::CreateTask(
    int priority, Time start, Time cycle, ExecutionSpecificationInterface* execution_specification)
{
    Task* task = new Task("TASK");

    task->SetPriority(priority);
    task->SetExecutionSpecification(execution_specification);

    m_suspended_task_list.push_back(task);

    return task;
}
void RoundRobin::InsertTask(Task* task)
{
    if(!task->GetMoveTaskState())
    {
        m_ready_task_list.insert(task);
    }
    else
    {

    }
}

void RoundRobin::Notify(int id)
{
	ActivateTask((Task*) id);
}

void RoundRobin::DeleteTask(Task* task)
{
    // Remove task from m_running_task.
    if(m_running_task == task)
    {
        m_running_task = nullptr;
        task->SetMoveTaskState(true);
        return;
    }
    // Remove task from m_ready_task_list.
    else if(!m_ready_task_list.empty())
    {
        set<Task*, bool (*)(const Task* lhs, const Task* rhs)> list(TaskCompare);
        bool task_found = false;
        unsigned int size = m_ready_task_list.size();
        for(unsigned int i = 0; i < size; i++)
        {
        	Task* top = *m_ready_task_list.begin();

            if(top != task)
            {
                list.insert(top);
                m_ready_task_list.erase(top);
            }
            else
            {
                task_found = true;
                m_ready_task_list.erase(top);
            }
        }
        if(task_found)
        {
            m_ready_task_list = list;
            return;
        }
    }
    // Remove task from m_suspended_task_list.
    else if(!m_suspended_task_list.empty())
    {
        std::list<Task*>::iterator it;
        for(it = m_suspended_task_list.begin(); it != m_suspended_task_list.end(); ++it)
        {
            if (task == *it)
            {
                m_suspended_task_list.erase(it);
                return;
            }
        }
    }
}

} // namespace ERNEST
