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
#ifndef ERNEST_SCHEDULER_HEADER
#define ERNEST_SCHEDULER_HEADER

#include <ernest/ernest_systemc.hpp>

namespace ERNEST
{
using namespace std;

class Task;
class ExecutionSpecificationInterface;

class Scheduler
{
public:
    /**
     * Destructor.
     */
    virtual ~Scheduler(void) {};

    /**
     * Creates a task to be used with this scheduler. The returned
     * task is already registered to this scheduler and may run when
     * scheduled.
     *
     * @param priority The priority of the created task.
     * @param execution_specification The execution specification of the task.
     * @return The created task.
     */
    virtual Task* CreateTask(int priority,
                             ExecutionSpecificationInterface* execution_specification) = 0;
    /**
     * Resumes a suspended or waiting task. Can be used to signal a
     * task that a resource is available now.
     *
     * @param task Task that should be resumed.
     */
    virtual void SignalTask(Task* task) = 0;

    /**
     * Determine the task that should run now and run it.
     */
    virtual void Schedule() = 0;

    /**
     * Terminate a task's execution. May only be called for a running
     * task.
     *
     * @param task The task to terminate.
     */
    virtual void TerminateTask(Task* task) = 0;
    virtual void DeleteTask(Task* task) = 0;
    virtual void InsertTask(Task* task) = 0;
};

} // namespace ERNEST

#endif /* ERNEST_SCHEDULER_HEADER */
