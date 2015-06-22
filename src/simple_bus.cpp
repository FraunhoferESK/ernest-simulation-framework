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
#define SC_INCLUDE_DYNAMIC_PROCESSES

#include <ernest/ernest_systemc.hpp>
#include <ernest/simple_bus.hpp>

namespace ERNEST
{

SimpleBus::SimpleBus(sc_module_name instname) : sc_module(instname)
{
}

void SimpleBus::EventProcess(sc_fifo<SimpleBusFrame>& channel)
{
    while(true) {
        wait(channel.data_written_event());

        SimpleBusFrame frame;
        // every frame is read and then written to the port out
        // channels
        while(channel.num_available() > 0) {
            frame = channel.read();

            wait(1, SC_MS);

            for(int i = 0; i < m_ports_out.size(); i++) {
                m_ports_out[i]->write(frame);
            }
        }
    }
}

void SimpleBus::AttachInterface(SimpleBusInterface* businterface)
{
    m_ports_out(businterface->GetChannelIn());
    m_ports_in(businterface->GetChannelOut());
    sc_spawn(sc_bind(&SimpleBus::EventProcess,
                     this,
                     sc_ref(businterface->GetChannelOut())));
}

} // namespace ERNEST
