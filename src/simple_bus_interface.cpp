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
#include <ernest/simple_bus_interface.hpp>
#include <ernest/ernest_addition.hpp>

namespace ERNEST
{

SimpleBusInterfaceId SimpleBusInterface::next_bus_interface_id = 1;

ostream& operator << (ostream& os, const ERNEST::SimpleBusFrame& frame)
{
    os << frame.signal_id << frame.source_id;

    for (int i = 0; i < frame.length; ++i) {
        os << frame.payload[i];
    }

    return os;
}

SimpleBusInterface::SimpleBusInterface(sc_module_name instname) : m_ecu(nullptr)
{
    m_read_buffer.length = 0;
    m_read_buffer.signal_id = 0;
    m_write_buffer.length = 0;
    m_write_buffer.signal_id = 0;
    m_bus_interface_out(m_channel_out);
    m_bus_interface_in(m_channel_in);
    m_interface_id = next_bus_interface_id++;

    SC_THREAD(Process);
}

void SimpleBusInterface::Process(void)
{
    while(true) {
        wait(m_bus_interface_in->data_written_event());

        // all frames (that where received at the same time) are
        // processed - only one data_written_event is triggered in
        // this situation
        while(m_bus_interface_in->num_available() > 0) {
            SimpleBusFrame buffer = m_bus_interface_in->read();

            // frame should only be stored as long as this interface
            // was not the sender
            if(buffer.source_id != m_interface_id) {
                m_read_buffer = buffer;
            }
        }
    }
}

void SimpleBusInterface::Transmit(SimpleBusFrame* frame)
{
    m_write_buffer.signal_id = frame->signal_id;
    m_write_buffer.source_id = m_interface_id;
    m_write_buffer.length = frame->length;
    memcpy(m_write_buffer.payload, frame->payload, frame->length);

    m_bus_interface_out->write(m_write_buffer);
}

void SimpleBusInterface::Receive(SimpleBusFrame* frame)
{
    frame->signal_id = m_read_buffer.signal_id;
    frame->source_id = m_read_buffer.source_id;
    frame->length = m_read_buffer.length;
    memcpy(frame->payload, m_read_buffer.payload, m_read_buffer.length);
    m_read_buffer.signal_id = 0;
}

sc_fifo<SimpleBusFrame>& SimpleBusInterface::GetChannelOut()
{
    return m_channel_out;
}

sc_fifo<SimpleBusFrame>& SimpleBusInterface::GetChannelIn()
{
    return m_channel_in;
}

void SimpleBusInterface::set_ecu(Ecu* ecu)
{
    m_ecu = ecu;
}

} // namespace ERNEST
