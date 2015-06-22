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
#ifndef SWF_MOVE_HPP
#define SWF_MOVE_HPP

#include <list>
#include <iostream>
#include <ernest/software_function.hpp>
#include <ernest/osek_os.hpp>

namespace ERNEST
{

class SwfMove : public SoftwareFunction
{
public:
    SwfMove(TaskContext *context);
    virtual ~SwfMove(void);

    void PullPorts();
    void Exec();
    void PushPorts();

    void SetMoveList(Task* task, Ecu* ecu);

private:
    list<Task*> m_task_list;
    list<Ecu*> m_ecu_list;
};

} // namespce ERNEST

#endif /* SWF_MOVE_HPP */
