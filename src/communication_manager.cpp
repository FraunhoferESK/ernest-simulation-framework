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
#include <queue>
#include <assert.h>
#include <ernest/ernest_addition.hpp>
#include <ernest/communication_manager.hpp>
#include <ernest/osek_os.hpp>

using namespace ERNEST;

CommunicationManager::CommunicationManager(OsekOS* os) : m_os(os)
{
}

void CommunicationManager::Update()
{
    if(m_os->GetEcu()->GetHardware<SimpleBusInterface>() != nullptr)
    {
        SimpleBusFrame data;
        SimpleBusInterface* vbd = m_os->GetEcu()->GetHardware<SimpleBusInterface>();

        // check if new data is available
        vbd->Receive(&data);
        m_os->ReceiveSignalRaw(data.signal_id, data.payload, data.length);
    }
    
    if(m_os->GetEcu()->GetHardware<CanBusInterface>() != nullptr)
    {
        CanBusFrame canData;
        CanBusInterface* cbd = m_os->GetEcu()->GetHardware<CanBusInterface>();

        // check if new data is available
        cbd->Receive(&canData);
        if(canData.message_id > 0) {
            std::cout << "CommunicationManager@"<<this->m_os->GetEcu()->name()<<"::ReceiveCanMessage: " << canData.message_id << " , Payload: " << canData.payload << std::endl;

            SignalId signal_id = m_can_in_mapping_table[canData.message_id];

            m_os->ReceiveSignalRaw(signal_id, canData.payload, canData.length);
        }
    }
}

void CommunicationManager::SetCanRoutingTable(SignalId signalId, CanId canId)
{
    m_can_out_routing_table.insert( pair<SignalId,CanId>(signalId, canId) );
    m_can_in_mapping_table.insert( pair<SignalId,CanId>(canId, signalId) );
}
