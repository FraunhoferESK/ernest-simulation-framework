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
#include <ernest/task.hpp>
#include <ernest/round_robin.hpp>
#include <ernest/ernest_addition.hpp>

namespace ERNEST
{

RoundRobin::RoundRobin() :  m_ready_task_list(TaskCompare), m_running_task(nullptr)
{
}

void RoundRobin::Schedule()
{
    // There is a task, but it has to be checked if it is still running
    if (m_running_task != nullptr) {
        assert(m_running_task->GetTaskState() == RUNNING);
    } else if (!m_ready_task_list.empty()) {
        StartTask();
    }
}

void RoundRobin::SignalTask(Task* task)
{

    if (task->GetTaskState() == RUNNING) {
        task->SimulationNotify();
        return;
    }

    if (task->GetTaskState() == SUSPENDED) {
        ActivateTask(task);
    }
}

void RoundRobin::ActivateTask(Task* task)
{
    assert(task->GetTaskState() == SUSPENDED);
    assert(task != m_running_task);
    m_suspended_task_list.remove(task);
    m_ready_task_list.push(task);
    task->SetState(READY);
}

void RoundRobin::TerminateTask(Task* task)
{
    if(!task->GetMoveTaskState())
    {
        assert(task->GetTaskState() == RUNNING);
        assert(m_running_task == task) ;
        m_running_task = nullptr;
        m_suspended_task_list.push_back(task);
        task->SetState(SUSPENDED);
        Schedule();
        task->SimulationWait();
    }
    else
    {
        task->SetMoveTaskState(false);
        m_suspended_task_list.push_back(task);
        task->SetState(SUSPENDED);
        Schedule();
        task->SimulationWait();
    }
}

void RoundRobin::StartTask()
{
    assert(m_running_task == nullptr);
    m_running_task = m_ready_task_list.top();
    m_ready_task_list.pop();
    m_running_task->SetState(RUNNING);
    m_running_task->SimulationNotify();
}

Task* RoundRobin::CreateTask(
    int priority, ExecutionSpecificationInterface* execution_specification)
{
    Task* task = new Task("TASK");

    task->SetScheduler(this);
    task->SetPriority(priority);
    task->SetExecutionSpecification(execution_specification);

    m_suspended_task_list.push_back(task);

    return task;
}
void RoundRobin::InsertTask(Task* task)
{
    if(!task->GetMoveTaskState())
    {
        task->SetScheduler(this);
        task->SetState(READY);
        m_ready_task_list.push(task);
    }
    else
    {
        task->SetScheduler(this);
    }
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
        priority_queue<Task*, vector<Task*>, bool (*)(const Task* lhs, const Task* rhs)> list(TaskCompare);
        bool task_found = false;
        unsigned int size = m_ready_task_list.size();
        for(unsigned int i = 0; i < size; i++)
        {
            if(m_ready_task_list.top() != task)
            {
                list.push(m_ready_task_list.top());
                m_ready_task_list.pop();
            }
            else
            {
                task_found = true;
                m_ready_task_list.pop();
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
