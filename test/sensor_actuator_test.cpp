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
#include <ernest/ernest.hpp>
#include "sensor_actuator_test.hpp"
#include "swf_sensor_actuator.hpp"

using namespace ERNEST;

void SensorActuatorTest::Execute(void)
{
    cout << "Executing FlowPortTest" << endl;
    Simulator::Init(L"ExteriorLight.ernest");
    Simulator::SetDuration(seconds(10));

    BinaryTraceRecorder trace_recorder("ExteriorLight.ernest.bt1");
    Simulator::SetTraceRecorder(&trace_recorder);

    // Declare ecu, sensor and actuator
    Ecu swf_ecu("swf ecu");
    Ecu sensor_ecu("s_ecu");
    Ecu actuator_ecu("a_ecu");
    SimpleSensor<int, 100> *sensor = sensor_ecu.AddHardware<SimpleSensor<int, 100> >();
    SimpleActuator<int, 200> *actuator = actuator_ecu.AddHardware<SimpleActuator<int, 200> >();

    // Attach ecu, sensor and actuator to bus
    SimpleBus bus("bus");
    bus.AttachInterface(swf_ecu.AddHardware<SimpleBusInterface>() );
    bus.AttachInterface(sensor_ecu.AddHardware<SimpleBusInterface>() );
    bus.AttachInterface(actuator_ecu.AddHardware<SimpleBusInterface>() );

    // Configure software of ecu
    swf_ecu.GetService<OsekOS>()->SetScheduler<RoundRobin>();
    sensor_ecu.GetService<OsekOS>()->SetScheduler<RoundRobin>();
    actuator_ecu.GetService<OsekOS>()->SetScheduler<RoundRobin>();

    Task* t = swf_ecu.GetService<OsekOS>()->DeclareTask<SwfSensorActuator>(0,
              milliseconds(0),
              milliseconds(50),
              new WorstCaseExecutionSpecification(milliseconds(120)));
    SwfSensorActuator* swf = dynamic_cast<SwfSensorActuator*>(t->GetSwf());

    // Set up communication
    connect_ports(sensor->data, swf->sensor_data_in);
    connect_ports(swf->actuator_data_out, actuator->data);

    Simulator::Start();
}

int sc_main(int argc, char* argv[])
{
    SensorActuatorTest::Execute();
    return 0;
}
