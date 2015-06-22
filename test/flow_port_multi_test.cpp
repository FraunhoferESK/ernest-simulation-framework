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
#include "swf_a.h"
#include "swf_b.h"
#include "flow_port_multi_test.hpp"


void FlowPortMultiTest::Execute(void)
{
    cout << "Executing FlowPortMultiTest" << endl;

    Simulator::Init(L"ExteriorLight.ernest");
    Simulator::SetDuration(seconds(10));

    BinaryTraceRecorder trace_recorder("ExteriorLight.ernest.bt1");
    trace_recorder.AddEventMapping("ExteriorLight.ernest#//@structureModel.0/@modules.23/@ports.3", 0);
    Simulator::SetTraceRecorder(&trace_recorder);
    //
    // Building the hardware topology
    //

    // Create ECU
    Ecu ecu1("ECU1");
    Ecu ecu2("ECU2");
    Ecu ecu3("ECU3");

    // Create the bus
    SimpleBus bus("SimpleBus");

    // Adding bus interfaces to ecus
    SimpleBusInterface *ecu1BusInterface = ecu1.AddHardware<SimpleBusInterface>();
    SimpleBusInterface *ecu2BusInterface = ecu2.AddHardware<SimpleBusInterface>();
    SimpleBusInterface *ecu3BusInterface = ecu3.AddHardware<SimpleBusInterface>();

    // Attaching the interfaces to the bus
    bus.AttachInterface(ecu1BusInterface);
    bus.AttachInterface(ecu2BusInterface);
    bus.AttachInterface(ecu3BusInterface);

    //
    // Configuring the software system
    //

    // Set scheduler
    OsekOS *os1 = ecu1.GetService<OsekOS>();
    OsekOS *os2 = ecu2.GetService<OsekOS>();
    OsekOS *os3 = ecu3.GetService<OsekOS>();

    os1->SetScheduler<RoundRobin>();
    os2->SetScheduler<RoundRobin>();
    os3->SetScheduler<RoundRobin>();

    // Create one task with two SWF
    Task* t1 = os1->DeclareTask<SwfA>(1,
                                      milliseconds(15),
                                      milliseconds(40),
                                      new WorstCaseExecutionSpecification(milliseconds(20)));
    Task* t2 = os2->DeclareTask<SwfB>(1,
                                      milliseconds(25),
                                      milliseconds(40),
                                      new WorstCaseExecutionSpecification(milliseconds(25)));
    Task* t3 = os3->DeclareTask<SwfB>(1,
                                      milliseconds(25),
                                      milliseconds(45),
                                      new WorstCaseExecutionSpecification(milliseconds(20)));

    SwfA* swfA = dynamic_cast<SwfA*>(t1->GetSwf());
    SwfB* swfB1 = dynamic_cast<SwfB*>(t2->GetSwf());
    SwfB* swfB2 = dynamic_cast<SwfB*>(t3->GetSwf());

    connect_ports(swfA->src_counter, swfB1->counter);
    connect_ports(swfA->src_counter, swfB2->counter);

    Simulator::Start();
}

int sc_main(int argc, char* argv[])
{
    FlowPortMultiTest::Execute();
    return 0;
}
