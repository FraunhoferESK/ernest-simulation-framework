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
#include "swf_b.h"
#include <ernest/osek_os.hpp>

using namespace std;

SwfB::SwfB(TaskContext* context) :
    SoftwareFunction(context),
    counter("port2", context)
{
}

void SwfB::PullPorts()
{
    counter.Pull();
}

void SwfB::Exec()
{
    cout << sc_time_stamp() << ": SwfB received: " << counter << endl;
    wait(10, SC_MS);
}

void SwfB::PushPorts()
{
    // No out ports - no action required
}
