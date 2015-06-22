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
#include <ernest/alarm.hpp>
#include "swf_a.h"

using namespace std;

SwfA::SwfA(TaskContext *context) :
    SoftwareFunction(context),
    src_counter("port1", context, "ExteriorLight.ernest#//@structureModel.0/@modules.23/@ports.3")
{
    src_counter = 0;
}

void SwfA::PullPorts()
{
    // #######################################################################
    // # Pull all in flow ports
    // #######################################################################

    // # End #################################################################
}

void SwfA::Exec()
{
    src_counter++;
    wait(10, SC_MS);
    cout << sc_time_stamp() << ": Task " << this->GetTask() << " SENDS: " << src_counter << endl << endl;
}


void SwfA::PushPorts()
{
    // #######################################################################
    // # Push all out flow ports
    // #######################################################################
    src_counter.Push();
    // # End #################################################################
}
