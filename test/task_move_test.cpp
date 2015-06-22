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
#include "task_move_test.hpp"
#include "swf_move.hpp"
#include "swf_a.h"
#include "swf_b.h"

using namespace ERNEST;

void TaskMoveTest::Execute(void)
{
    cout << "Executing TaskMoveTest" << endl;
    Simulator::Init(L"ExteriorLight.ernest");
    Simulator::SetDuration(seconds(15));

    BinaryTraceRecorder trace_recorder("ExteriorLight.ernest.bt1");
    Simulator::SetTraceRecorder(&trace_recorder);

    /*
     * Building the hardware topology
     */

    // Create ECU
    Ecu ecu1("ECU1");
    Ecu ecu2("ECU2");

    // Create the bus
    SimpleBus bus("SimpleBus");

    // Adding bus interfaces to ecus
    SimpleBusInterface *ecu1BusInterface = ecu1.AddHardware<SimpleBusInterface>();
    SimpleBusInterface *ecu2BusInterface = ecu2.AddHardware<SimpleBusInterface>();

    // Attaching the interfaces to the bus
    bus.AttachInterface(ecu1BusInterface);
    bus.AttachInterface(ecu2BusInterface);

    /*
     * Configuring the software system
     */

    // Set scheduler
    OsekOS *os1 = ecu1.GetService<OsekOS>();
    OsekOS *os2 = ecu2.GetService<OsekOS>();

    os1->SetScheduler<RoundRobin>();
    os2->SetScheduler<RoundRobin>();

    // Create tasks
    NormalExecutionSpecification* normal = new NormalExecutionSpecification(milliseconds(15), milliseconds(5));

    Task* t11 = ecu1.GetService<OsekOS>()->DeclareTask<SwfA>(0, milliseconds(0), milliseconds(30), normal);
    Task* t12 = ecu1.GetService<OsekOS>()->DeclareTask<SwfB>(0, milliseconds(0), milliseconds(30), normal);
    SwfA* swf_a1 = dynamic_cast<SwfA*>(t11->GetSwf());
    SwfB* swf_b1 = dynamic_cast<SwfB*>(t12->GetSwf());
    connect_ports(swf_a1->src_counter, swf_b1->counter);

    Task* t21 = ecu1.GetService<OsekOS>()->DeclareTask<SwfA>(0, milliseconds(0), milliseconds(30), normal);
    Task* t22 = ecu1.GetService<OsekOS>()->DeclareTask<SwfB>(0, milliseconds(0), milliseconds(30), normal);
    SwfA* swf_a2 = dynamic_cast<SwfA*>(t21->GetSwf());
    SwfB* swf_b2 = dynamic_cast<SwfB*>(t22->GetSwf());
    connect_ports(swf_a2->src_counter, swf_b2->counter);

    Task* t31 = ecu1.GetService<OsekOS>()->DeclareTask<SwfA>(0, milliseconds(0), milliseconds(30), normal);
    Task* t32 = ecu1.GetService<OsekOS>()->DeclareTask<SwfB>(0, milliseconds(0), milliseconds(30), normal);
    SwfA* swf_a3 = dynamic_cast<SwfA*>(t31->GetSwf());
    SwfB* swf_b3 = dynamic_cast<SwfB*>(t32->GetSwf());
    connect_ports(swf_a3->src_counter, swf_b3->counter);

    //Task* t41 = ecu1.GetService<OsekOS>()->DeclareTask<SwfA>(0, sc_time(0.0, SC_MS), sc_time(30.0, SC_MS), normal);
    //Task* t42 = ecu1.GetService<OsekOS>()->DeclareTask<SwfB>(0, sc_time(0.0, SC_MS), sc_time(30.0, SC_MS), normal);
    //SwfA* swf_a4 = dynamic_cast<SwfA*>(t41->GetSwf());
    //SwfB* swf_b4 = dynamic_cast<SwfB*>(t42->GetSwf());
    //connect_ports(swf_a4->src_counter, swf_b4->counter);

    /*
     * Configure task move
     */

    // Create the task to call the move function
    Task* task_move = ecu2.GetService<OsekOS>()->DeclareTask<SwfMove>(0, milliseconds(0), milliseconds(500), normal);
    SwfMove* swf_move = dynamic_cast<SwfMove*>(task_move->GetSwf());

    // Move tasks
    swf_move->SetMoveList(t11, &ecu2);
    //swf_move->SetMoveList(t41, &ecu2);
    swf_move->SetMoveList(t31, &ecu2);
    swf_move->SetMoveList(t22, &ecu2);
    swf_move->SetMoveList(t32, &ecu2);
    swf_move->SetMoveList(t21, &ecu2);
    //swf_move->SetMoveList(t42, &ecu2);
    swf_move->SetMoveList(t12, &ecu2);

    swf_move->SetMoveList(t11, &ecu1);
    //swf_move->SetMoveList(t41, &ecu1);
    swf_move->SetMoveList(t21, &ecu1);
    //swf_move->SetMoveList(t42, &ecu1);
    swf_move->SetMoveList(t12, &ecu1);
    swf_move->SetMoveList(t31, &ecu1);
    swf_move->SetMoveList(t22, &ecu1);
    swf_move->SetMoveList(t32, &ecu1);

    swf_move->SetMoveList(t11, &ecu2);
    swf_move->SetMoveList(t21, &ecu2);
    //swf_move->SetMoveList(t42, &ecu2);
    //swf_move->SetMoveList(t41, &ecu2);
    swf_move->SetMoveList(t31, &ecu2);
    swf_move->SetMoveList(t22, &ecu2);
    swf_move->SetMoveList(t32, &ecu2);
    swf_move->SetMoveList(t12, &ecu2);

    swf_move->SetMoveList(t31, &ecu1);
    swf_move->SetMoveList(t22, &ecu1);
    swf_move->SetMoveList(t32, &ecu1);
    swf_move->SetMoveList(t11, &ecu1);
    //swf_move->SetMoveList(t41, &ecu1);
    swf_move->SetMoveList(t21, &ecu1);
    //swf_move->SetMoveList(t42, &ecu1);
    swf_move->SetMoveList(t12, &ecu1);

    /*
     * Start simulation
     */

    Simulator::Start();
}

int sc_main(int argc, char* argv[])
{
    TaskMoveTest::Execute();
    return 0;
}
