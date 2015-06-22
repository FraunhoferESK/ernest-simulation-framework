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
#ifndef ERNEST_CAN_BUS_INTERFACE_HEADER
#define ERNEST_CAN_BUS_INTERFACE_HEADER

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "ernest_systemc.hpp"
#include "ernest_addition.hpp"
#include "ecu.hpp"

#define CAN_BUS_FRAME_LENGTH 8


namespace ERNEST {
using namespace std;

typedef unsigned int CanId;
   /**
    * Defines an ID structure for CanBusInterface.
    */
typedef unsigned int CanBusInterfaceId;

    /**
     * @struct CanBusFrame
     * a packet that goes through the CAN-Bus
     */
struct CanBusFrame
{
public:

    /**
     * MessageIdentifier (0..2047) (11bit) respectively (0..536870911)(29 bit)
     */
    CanId message_id;

    /**
     * Length of the available payload.
     */
    int length;

    /**
     * contains the data
     */
    char payload[CAN_BUS_FRAME_LENGTH];

    /**
     * id of the interface seding the frame
     */
    CanBusInterfaceId interface_id;
};

/**
 * << operator for the CanBusFrame structure.
 * Required by SystemC internally, currently no other purpose
 *
 * @param os output stream
 * @param frame CanBusFrame that is written to the output stream
 */
ostream& operator << (ostream& os, const ERNEST::CanBusFrame &frame);

SC_MODULE(CanBusInterface)
{
public:
    SC_HAS_PROCESS(CanBusInterface);
    CanBusInterface(sc_module_name instname);

    void Process(void);
    
    /**
     * Copies the contents of the given frame into the write buffer and
     * transmits the data to the connected can bus.
     *
     * @param frame
     */
    void Transmit(CanBusFrame* frame);

    /**
     * Copies the contents of the (current frame in the) read buffer
     * to the given frame reference.
     *
     * @param frame
     */
    void Receive(CanBusFrame* frame);

    /**
     * Returns the SystemC channel for incoming data.
     * Is called by the CanBus to create a connection with this interface.
     *
     * @return channel out
     */
    sc_fifo<CanBusFrame>& GetChannelOut();

    /**
     * Returns the SystemC channel for incoming data.
     * Is called by the CanBus to create a connection with this interface.
     *
     * @return channel in
     */
    sc_fifo<CanBusFrame>& GetChannelIn();

    /**
     * Sets a reference to the Ecu.
     * Is called by the Ecu when attaching the interface as a
     * new hardware component.
     *
     * @param ecu pointer to Ecu
     */
    void set_ecu(Ecu* ecu);

private:
    CanBusInterface(const CanBusInterface&);
    CanBusInterface& operator=(const CanBusInterface&);

    /**
     * SystemC Port Out.
     */
    sc_port<sc_fifo_out_if<CanBusFrame> > bus_interface_out_;

    /**
     * SystemC Port In.
     */
    sc_port<sc_fifo_in_if<CanBusFrame> > bus_interface_in_;

    /**
     * Channel Out for data transmission to the Bus.
     */
    sc_fifo<CanBusFrame> channel_out_;

    /**
     * Channel In for data transmission from the Bus.
     */
    sc_fifo<CanBusFrame> channel_in_;

    /**
     * Buffer of one Frame for incoming data.
     */
    CanBusFrame read_buffer_;

    /**
     * Buffer of one Frame for outgoing data.
     */
    CanBusFrame write_buffer_;

    /**
     * ID of this Interface.
     */
    CanBusInterfaceId interface_id_;

    /**
     * Reference to the Ecu which this Interface belongs to.
     */
    Ecu* ecu_;

    /**
     * Holds the ID that the next BusInterface will receive when created.
     */
    static CanBusInterfaceId next_bus_interface_id;
};

} // namespace ERNEST

#endif /* ERNEST_CAN_BUS_INTERFACE_HEADER */
