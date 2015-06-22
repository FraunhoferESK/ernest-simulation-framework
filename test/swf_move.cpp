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
#include "swf_move.hpp"

using namespace ERNEST;

SwfMove::SwfMove(TaskContext *context) : 
        SoftwareFunction(context)
{
}

SwfMove::~SwfMove(void)
{
}

void SwfMove::PullPorts()
{
}

void SwfMove::Exec()
{
    if(!m_task_list.empty() && !m_ecu_list.empty())
    {
    	// TODO: Task moving functions have to be reimplemented
        // m_task_list.front()->GetEcu()->GetService<OsekOS>()->RemoveTaskFromEcu(m_task_list.front(), m_ecu_list.front());
        // m_ecu_list.front()->GetService<OsekOS>()->InsertTaskIntoECU(m_task_list.front(), m_ecu_list.front());

        m_task_list.pop_front();
        m_ecu_list.pop_front();
    }
}

void SwfMove::PushPorts()
{
}

void SwfMove::SetMoveList(Task* task, Ecu* ecu)
{
    m_task_list.push_back(task);
    m_ecu_list.push_back(ecu);
}
