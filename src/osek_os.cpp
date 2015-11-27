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
#include <ernest/simulator.hpp>
#include <ernest/ernest_addition.hpp>
#include <ernest/osek_os.hpp>
#include <ernest/alarm.hpp>
#include <ernest/runtime_environment.hpp>
#include <ernest/communication_manager.hpp>
#include <ernest/can_bus_interface.hpp>
#include <ernest/time.hpp>

namespace ERNEST
{
OsekOS::OsekOS(Ecu* ecu) : Service(ecu)
{
    m_scheduler = nullptr;
    m_timer = new Timer();
    m_rte = new RuntimeEnvironment(this);
    m_com = new CommunicationManager(this);
}

OsekOS::~OsekOS()
{
    delete m_timer;
    delete m_rte;
    delete m_com;
}

void OsekOS::Update()
{
    m_com->Update();
    m_timer->Update(this);
    m_scheduler->Update(this);
}

RuntimeEnvironment* OsekOS::GetRuntimeEnvironment()
{
	return m_rte;
}

CommunicationManager* OsekOS::GetCommunicationManager()
{
	return m_com;
}

Timer* OsekOS::GetTimer()
{
	return m_timer;
}

void OsekOS::ReceiveSignalRaw(SignalId signal_id, void* data, size_t length)
{
    m_rte->ReceiveSignalRaw(signal_id, data, length);
}

void OsekOS::SignalTask(Task* task)
{
    m_scheduler->SignalTask(task);
}

void OsekOS::SetCanRoutingTable(SignalId signalId, CanId canId)
{
    m_com->SetCanRoutingTable(signalId, canId);
}

void OsekOS::DeclareAlarm(Time start, Time cycle, Task* task)
{
    // Setting up of Alarm for DeclareTask.
    m_timer->SetRelAlarm(m_scheduler, 0, start, cycle);
}

void OsekOS::DeclareAlarm(double start, double cycle, Task* task)
{
    DeclareAlarm(milliseconds(start), milliseconds(cycle), task);
}

} // namespace ERNEST

