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
#ifndef ERNEST_SIMPLE_BUS_INTERFACE_HEADER
#define ERNEST_SIMPLE_BUS_INTERFACE_HEADER

#include "ernest_systemc.hpp"
#include "ernest_addition.hpp"
#include "ecu.hpp"
#include "signal.hpp"

#define BUS_FRAME_LENGTH 1000

namespace ERNEST
{
using namespace std;

typedef unsigned int SimpleBusInterfaceId;

struct SimpleBusFrame {
public:
    SignalId signal_id;
    SimpleBusInterfaceId source_id;
    int length;
    char payload[BUS_FRAME_LENGTH];
};

/**
 * << operator for the SimpleBusFrame structure.
 * Required by SystemC internally, currently no other purpose
 *
 * @param os output stream
 * @param frame SimpleBusFrame that is written to the output stream
 */
ostream& operator << (ostream& os, const ERNEST::SimpleBusFrame& frame);

SC_MODULE(SimpleBusInterface)
{
public:
    SC_HAS_PROCESS(SimpleBusInterface);
    SimpleBusInterface(sc_module_name instname);

    void Process(void);

    /**
     * Copies the contents of the given frame into the write buffer and
     * transmits the data to the connected bus.
     *
     * @param frame
     */
    void Transmit(SimpleBusFrame * frame);
    /**
     * Copies the contents of the (current frame in the) read buffer
     * to the given frame reference.
     *
     * @param frame
     */
    void Receive(SimpleBusFrame * frame);

    /**
     * Returns the SystemC Channel for incoming data.
     * Is called by the Bus to create a connection with this interface.
     *
     * @return channel out
     */
    sc_fifo<SimpleBusFrame>& GetChannelOut();

    /**
     * Returns the SystemC Channel for Incoming data.
     * Is called by the Bus to create a connection with this interface.
     *
     * @return channel in
     */
    sc_fifo<SimpleBusFrame>& GetChannelIn();

    /**
     * Sets the Ecu.
     * Is called by the Ecu when attaching the Interface as a
     * new hardware component.
     *
     * @param ecu Pointer to the Ecu
     */
    void set_ecu(Ecu* ecu);

private:
    SimpleBusInterface(const SimpleBusInterface&);
    SimpleBusInterface& operator=(const SimpleBusInterface&);
    sc_port<sc_fifo_out_if<SimpleBusFrame> > m_bus_interface_out;
    sc_port<sc_fifo_in_if<SimpleBusFrame> > m_bus_interface_in;
    sc_fifo<SimpleBusFrame> m_channel_out;
    sc_fifo<SimpleBusFrame> m_channel_in;

    SimpleBusFrame m_read_buffer;
    SimpleBusFrame m_write_buffer;

    SimpleBusInterfaceId m_interface_id;
    Ecu* m_ecu;

    static SimpleBusInterfaceId next_bus_interface_id;
};

} // namespace ERNEST

#endif /* ERNEST_SIMPLE_BUS_INTERFACE_HEADER */
