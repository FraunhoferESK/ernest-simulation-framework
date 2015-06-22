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
#include "swf_req.hpp"

using namespace std;

SwfReq::SwfReq(TaskContext* context) :
    SoftwareFunction(context),
    source("port1", context)
{
}

void SwfReq::PullPorts()
{
}

void SwfReq::Exec()
{
    std::cout << sc_time_stamp() << " :Client Calls: bar(10.5, 7.0)"
              << std::endl;
    source->foo(3);
    source->bar(10.5, 7.0);
}

void SwfReq::PushPorts()
{
}
