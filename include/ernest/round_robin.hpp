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
#ifndef ERNEST_ROUND_ROBIN_HEADER
#define ERNEST_ROUND_ROBIN_HEADER

#include <queue>
#include <list>
#include <ernest/scheduler.hpp>
#include <ernest/execution_specification_interface.hpp>

namespace ERNEST {
using namespace std;

bool TaskCompare(const Task* lhs, const Task* rhs);

class RoundRobin : public Scheduler
{
public:
    RoundRobin();

    /**
     * Function CreateTask used for creating a task which is pointing to Task.
     *
     * @param priority The priority of the particular task.
     * @param execution_specification The execution specification of the task.
     * @return new task.
     */
    Task* CreateTask(int priority, ExecutionSpecificationInterface* execution_specification);

    void SignalTask(Task* task);
    void Schedule();
    void TerminateTask(Task* task);
    void StartTask();

    /**
     * Removes the task from scheduler in order to move it
     *
     * @param task Reference to the task to be moved.
     */
    void DeleteTask(Task* task);

    /**
     * Inserts a task in m_ready_task_list
     *
     * used for after moving this task from original OS
     *
     * @param task Reference to the moved task
     */
    void InsertTask(Task* task);

private:
    RoundRobin(const RoundRobin&);
    RoundRobin& operator=(const RoundRobin&);
    void ActivateTask(Task* task);
    list<Task*> m_suspended_task_list;
    priority_queue<Task*, vector<Task*>, bool (*)(const Task* lhs, const Task* rhs)> m_ready_task_list;
    list<Task*> m_waiting_task_list;
    Task* m_running_task;
};

} // namespace ERNEST

#endif /* ERNEST_ROUND_ROBIN_HEADER */
