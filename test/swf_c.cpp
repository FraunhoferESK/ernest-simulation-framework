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
#include <iostream>
#include <ernest/ernest_systemc.hpp>
#include <ernest/osek_os.hpp>
#include "swf_c.h"

SwfC::SwfC(TaskContext* context) :
    SoftwareFunction(context),
    in_counter("port_in", context),
    out_counter("port_out", context)
{
}

void SwfC::PullPorts()
{
    in_counter.Pull();
}

void SwfC::Exec()
{
    out_counter = in_counter;
    wait(10, SC_MS);
    cout << sc_time_stamp() << ": SwfC receiving: " << in_counter << endl;
    cout << sc_time_stamp() << ": SwfC sending: " << out_counter << endl;
}

void SwfC::PushPorts()
{
    out_counter.Push();
}
