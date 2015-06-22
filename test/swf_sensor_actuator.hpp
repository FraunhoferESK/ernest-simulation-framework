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
#ifndef SWF_SENSOR_ACTUATOR_HPP
#define SWF_SENSOR_ACTUATOR_HPP

#include <ernest/software_function.hpp>
#include <ernest/flow_port.hpp>

namespace ERNEST
{
class SwfSensorActuator : public SoftwareFunction
{
public:
    SwfSensorActuator(TaskContext *context);
    virtual ~SwfSensorActuator(void);

    void Exec();
    void PullPorts();
    void PushPorts();

    FlowPort<int, In> sensor_data_in;
    FlowPort<int, Out> actuator_data_out;
};

} // namespace ERNEST

#endif /* SWF_SENSOR_ACTUATOR_HPP */
