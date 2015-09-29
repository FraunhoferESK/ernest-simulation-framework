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
#include <ernest/software_function.hpp>
#include <ernest/communication_manager.hpp>
#include <ernest/task.hpp>
#include <ernest/osek_os.hpp>
#include <ernest/alarm.hpp>
#include <ernest/alarm_listener.hpp>
#include <ernest/scheduler.hpp>
#include <ernest/time.hpp>

namespace ERNEST
{

SoftwareFunction::SoftwareFunction(TaskContext* context)
{
    m_context = context;
}

void SoftwareFunction::SetTask(Task* task)
{
    m_context->task = task;
}

Task* SoftwareFunction::GetTask()
{
    return m_context->task;
}

void SoftwareFunction::WaitEvent()
{

}

} // namespace ERNEST
