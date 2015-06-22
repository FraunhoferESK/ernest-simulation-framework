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
#ifndef ERNEST_COMMUNICATION_MANAGER_HEADER
#define ERNEST_COMMUNICATION_MANAGER_HEADER

#include <map>
#include "ernest_addition.hpp"
#include "signal.hpp"
#include "simple_bus_interface.hpp"
#include "can_bus_interface.hpp"
#include "osek_os.hpp"

namespace ERNEST
{

/**
 * Class providing the Communication Manager responsible to handle
 * data communication.
 */
class CommunicationManager
{
public:
    /**
     * CommunicationManager communicate model with OS.
     *
     * @param os is an OsekOS pointer
     */
    CommunicationManager(OsekOS* os);

    /**
     * Function for updating communication ports.
     */
    void Update(void);

    /**
     * Transmits data via a specific communication bus.
     *
     * @param singal_id is the id of the signal
     * @param data is a pointer to the data to be transmitted
     * @param bus is a communication bus
     */
    template <class TransmitType>
    void TransmitOverBus(SignalId signal_id,
                         TransmitType &data,
                         Communication bus)
    {
        switch(bus) {
        case Simple:
            SimpleBusFrame simpleFrame;
            simpleFrame.signal_id = signal_id;
            simpleFrame.length = sizeof(TransmitType);

            memcpy(simpleFrame.payload, &data, simpleFrame.length);
            m_os->GetEcu()->GetHardware<SimpleBusInterface>()->Transmit(&simpleFrame);
            break;
        case Can:
            CanBusFrame canFrame;
            canFrame.message_id = m_can_out_routing_table[signal_id];
            canFrame.length = sizeof(TransmitType);
            canFrame.interface_id = -1;

            memcpy(canFrame.payload, &data, canFrame.length);
            m_os->GetEcu()->GetHardware<CanBusInterface>()->Transmit(&canFrame);
            break;
        default:
            cerr << "ERROR: CommunicationManager::TransmitOverBus - Bus "
                 << bus << "not existing!" << endl;
            break;
        }
    }

    /**
     * Receive signal id and data.
     *
     * @param signal_id is the id of the received data.
     * @param data is the received data.
     */
    void RxIndication(SignalId signal_id, SignalData data);

    /**
     * Set ECU running.
     *
     * @param port is the Portid of the data.
     * @param ecu is a pointer to ECU,
     */
    void SetRunningEcu(PortId port, Ecu* ecu);

    /**
     * Get back the Id.
     *
     * @param port is the Portid of the data.
     */
    Ecu* GetRunningEcu(PortId port);

    /**
     * Assigning routing table for CAN bus.
     *
     * @param signalId represents the id of the corresponding Signal.
     * @param canId represents the id of the CAN port.
     */
    void SetCanRoutingTable(SignalId signalId, CanId canId);

private:
    CommunicationManager(const CommunicationManager&);
    CommunicationManager& operator=(const CommunicationManager&);
    OsekOS *m_os;
    map<SignalId, CanId> m_can_out_routing_table;
    map<CanId, SignalId> m_can_in_mapping_table;
};

} // namespace ERNEST

#endif /* ERNEST_COMMUNICATION_MANAGER_HEADER */
