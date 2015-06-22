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
#include "swf_req.hpp"
#include "swf_prov.hpp"
#include "client_server_port_test.hpp"

using namespace ERNEST;

class Timer;
class Scheduler;
class CommunicationManager;
class RuntimeEnvironment;

void ClientServerPortTest::Execute(void)
{
    cout << "Executing ClientServerPortTest" << endl;

    Simulator::Init(L"ExteriorLight.ernest");
    Simulator::SetDuration(seconds(10));

    // Building the hardware topology
    // Create ECU
    Ecu ecu1("ECU1");
    Ecu ecu2("ECU2");

    // Create the bus
    SimpleBus bus("SimpleBus");

    // Adding bus interfaces to ecus
    SimpleBusInterface* ecu1_bus_interface =
        ecu1.AddHardware<SimpleBusInterface>();
    SimpleBusInterface* ecu2_bus_interface =
        ecu2.AddHardware<SimpleBusInterface>();

    // Attaching the interfaces to the bus
    bus.AttachInterface(ecu1_bus_interface);
    bus.AttachInterface(ecu2_bus_interface);

    // Configuring the software system

    // Set scheduler
    OsekOS* os1 = ecu1.GetService<OsekOS>();
    OsekOS* os2 = ecu2.GetService<OsekOS>();

    os1->SetScheduler<RoundRobin>();
    os2->SetScheduler<RoundRobin>();

    // Create one task with two SWF
    Task* t1 = os1->DeclareTask<SwfReq>(1,
                                        milliseconds(15),
                                        milliseconds(40),
                                        new WorstCaseExecutionSpecification(milliseconds(20)));
    Task* t2 = os2->DeclareTask<SwfProv>(1,
                                         milliseconds(25),
                                         milliseconds(0),
                                         new WorstCaseExecutionSpecification(milliseconds(20)));

    SwfReq* swf_req = dynamic_cast<SwfReq*>(t1->GetSwf());
    SwfProv* swf_prov = dynamic_cast<SwfProv*>(t2->GetSwf());

    connect_ports(swf_req->source, swf_prov->destination);

    Simulator::Start();
}

int sc_main(int argc, char* argv[])
{
    ClientServerPortTest::Execute();
    return 0;
}
