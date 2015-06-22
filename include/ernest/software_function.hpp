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
#ifndef ERNEST_SOFTWARE_FUNCTION_HEADER
#define ERNEST_SOFTWARE_FUNCTION_HEADER

#include <string>
#include <map>
#include "ernest_systemc.hpp"
#include "task.hpp"

namespace ERNEST
{

class AlarmListener;
class Task;
class OsekOS;
struct TaskContext;
class Timer;
class Event;
class Scheduler;

/**
 * Class represents a software function.
 */
class SoftwareFunction
{
public:
    /**
     * Constructor for Software Function.
     *
     * @param context as TaskContext
     */
    SoftwareFunction(TaskContext *context);
    virtual ~SoftwareFunction();

    virtual void PullPorts() = 0;
    virtual void Exec() = 0;
    virtual void PushPorts() = 0;

    /**
     * Function for SetTask for Setting a particular Task.
     *
     * @param task is a pointer to task.
     */
    void SetTask(Task* task);

    /**
     * Function SetAbsAlarm for accessing Task from the Software Function.
     *
     * @param listener for accessing the alarm.
     * @param start for setting the start time of the task.
     * @param cycle will give the period of execution of task.
     */
    void SetAbsAlarm(AlarmListener* listener, double start, double cycle);

    /**
     * Function SetRelAlarm for accessing Task from the Software Function.
     *
     * @param listener for accessing the alarm.
     * @param start for setting the start time of the task.
     * @param cycle will give the period of execution of task.
     */
    void SetRelAlarm(AlarmListener* listener, double start, double cycle);

    /**
     * Function GetTask for getting the Task for the software function.
     *
     * @return pointer to task
     */
    Task* GetTask();

protected:
    TaskContext* m_context;

    /**
     * Function WaitEvent for waiting the Task for getting the
     * scheduler.
     */
    void WaitEvent();

    /**
     * Function GetEvent for getting a particular Event.
     *
     * @param task is a pointer to task.
     * @param mask is an integer describing a mask.
     */
    void GetEvent(Task* task, int mask);

private:
    /**
     * Disable copy constructor
     */
    SoftwareFunction(const SoftwareFunction&);

    /**
     * Disable copy assignment operator
     */
    SoftwareFunction& operator=(const SoftwareFunction&);

    void DeclareAlarm(Alarm*);

    Timer* m_timer;
};

} // namespace ERNEST

#endif /* ERNEST_SOFTWARE_FUNCTION_HEADER */
