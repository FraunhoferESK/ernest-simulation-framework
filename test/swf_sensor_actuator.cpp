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
#include "swf_sensor_actuator.hpp"

using namespace ERNEST;

SwfSensorActuator::SwfSensorActuator(TaskContext *context) : SoftwareFunction(context), 
        sensor_data_in("sensor data in", context),
        actuator_data_out("actuator data out", context)
{
}

SwfSensorActuator::~SwfSensorActuator(void)
{
}

void SwfSensorActuator::PullPorts()
{
    sensor_data_in.Pull();
}

void SwfSensorActuator::Exec()
{
    actuator_data_out = sensor_data_in;
    cout << "Time: " << sc_time_stamp() << endl;;
    cout << "The swf transfers data: " << actuator_data_out << endl;
}

void SwfSensorActuator::PushPorts()
{
    actuator_data_out.Push();
}
