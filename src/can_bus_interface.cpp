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
#include <ernest/can_bus_interface.hpp>
#include <ernest/ernest_addition.hpp>

using namespace ERNEST;

namespace ERNEST {

CanBusInterfaceId CanBusInterface::next_bus_interface_id = 1;

ostream& operator << (ostream& os, const ERNEST::CanBusFrame &frame)
{
    os << frame.message_id << frame.message_id;
    os << frame.interface_id << frame.interface_id;

    for (int i = 0; i < frame.length; ++i)
    {
        os << frame.payload[i];
    }

    return os;
}
} // namespace ERNEST

CanBusInterface::CanBusInterface(sc_module_name instname) : ecu_(nullptr)
{
    read_buffer_.length = 0;
    read_buffer_.message_id = 0;
    write_buffer_.length = 0;
    write_buffer_.message_id = 0;
    bus_interface_out_(channel_out_);
    bus_interface_in_(channel_in_);
    interface_id_ = next_bus_interface_id++;

    SC_THREAD(Process);
}

void CanBusInterface::Process(void)
{
    while(true) {
        wait(bus_interface_in_->data_written_event());

        // all frames (that where received at the same time) are processed
        // - only one data_written_event is triggered in this situation
        while(bus_interface_in_->num_available() > 0) {
            CanBusFrame buffer = bus_interface_in_->read();

            // frame should only be stored as long as this interface was not the sender
            if(buffer.interface_id != interface_id_) {
                read_buffer_ = buffer;
                //cout << "CanBusInterface data received (" << ecu_->name() << ")" << endl;
            }
        }
    }
}

void CanBusInterface::Transmit(CanBusFrame* frame)
{
    write_buffer_.message_id = frame->message_id;
    write_buffer_.length = frame->length;
    write_buffer_.interface_id = interface_id_;
    memcpy(write_buffer_.payload, frame->payload, frame->length);

    bus_interface_out_->write(write_buffer_);
}

void CanBusInterface::Receive(CanBusFrame* frame)
{
    frame->message_id = read_buffer_.message_id;
    frame->length = read_buffer_.length;
    frame->interface_id = read_buffer_.interface_id;
    memcpy(frame->payload, read_buffer_.payload, read_buffer_.length);

    // clear buffer after receiving data
    read_buffer_.message_id = 0;
    for(int i = 0; i < CAN_BUS_FRAME_LENGTH; i++) {
        read_buffer_.payload[i] = 0;
    }
    read_buffer_.length = 0;
    read_buffer_.interface_id = 0;
}

sc_fifo<CanBusFrame>& CanBusInterface::GetChannelOut()
{
    return channel_out_;
}

sc_fifo<CanBusFrame>& CanBusInterface::GetChannelIn()
{
    return channel_in_;
}

void CanBusInterface::set_ecu(Ecu* ecu)
{
    ecu_ = ecu;
}
