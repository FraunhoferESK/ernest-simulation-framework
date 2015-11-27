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
#include <ernest/alarm_listener.hpp>
#include <ernest/time.hpp>
#include <ernest/osek_service.hpp>

namespace ERNEST
{
using namespace std;

class Task;
class ExecutionSpecificationInterface;
class OsekOS;

class Scheduler : public AlarmListener, public OsekService
{
public:
    /**
     * Destructor.
     */
    virtual ~Scheduler() {};

    /**
     * Determine the task that should run now and run it.
     */
    virtual void Update(OsekOS* osekos) = 0;

    /**
     * Creates a task to be used with this scheduler. The returned
     * task is already registered to this scheduler and may run when
     * scheduled.
     *
     * @param priority The priority of the created task.
     * @param execution_specification The execution specification of the task.
     * @return The created task.
     */
    virtual Task* CreateTask(int priority, Time start, Time cycle,
                             ExecutionSpecificationInterface* execution_specification) = 0;
    /**
     * Resumes a suspended or waiting task. Can be used to signal a
     * task that a resource is available now.
     *
     * @param task Task that should be resumed.
     */
    virtual void SignalTask(Task* task) = 0;

    /**
     * Activates a task that was previously suspended or terminated
     *
     * @param task Task that should be activated.
     */
    virtual void ActivateTask(Task* task) = 0;

    /**
     * Terminates a running ar active task
     *
     * @param task Task that should be terminated.
     */
    virtual void TerminateTask(Task* task) = 0;
};

} // namespace ERNEST

#endif /* ERNEST_SCHEDULER_HEADER */
