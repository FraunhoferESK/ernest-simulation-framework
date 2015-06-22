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
#ifndef ERNEST_SIMPLE_BUS_HEADER
#define ERNEST_SIMPLE_BUS_HEADER

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "ernest_systemc.hpp"
#include "simple_bus_interface.hpp"

namespace ERNEST
{
using namespace std;

/**
 * ERNEST Module for a simple bus.
 */
SC_MODULE(SimpleBus)
{
public:
    SC_HAS_PROCESS(SimpleBus);

    /**
     * Constructor.
     *
     * @param instname Name of the module.
     */
    SimpleBus(sc_module_name instname);

    /**
     * This function is running as a dynamic process.
     *
     * One process is running for every port in channel. This enables
     * the bus on every channel to wait for a data_written_event.
     *
     * @param channel Channel for this eventprocess.
     */
    void EventProcess(sc_fifo<SimpleBusFrame>& channel);

    /**
     * Connects a Bus Interface to the SimpleBus.
     *
     * @param businterface Interface to attach.
     */
    void AttachInterface(SimpleBusInterface * businterface);

private:
    /**
     * Disable copy constructor.
     */
    SimpleBus(const SimpleBus&);

    /**
     * Disable copy assignment operator.
     */
    SimpleBus& operator=(const SimpleBus&);

    sc_port<sc_fifo_out_if<SimpleBusFrame>, 0> m_ports_out;
    sc_port<sc_fifo_in_if<SimpleBusFrame>, 0> m_ports_in;
};

} // namespace ERNEST

#endif /* ERNEST_SIMPLE_BUS_HEADER */
