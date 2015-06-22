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
#include <assert.h>
#include <iostream>
#include <ernest/ernest_addition.hpp>
#include <ernest/runtime_environment.hpp>

namespace ERNEST
{

RuntimeEnvironment::RuntimeEnvironment(OsekOS* os) : m_os(os)
{
}

void RuntimeEnvironment::ReceiveSignalRaw(SignalId signal_id, void* data, size_t length)
{
    GenericObjectBuffer* buffer = m_signal_buffer[signal_id];

    // If buffer is nullptr, we just received a signal which was broadcasted
    // and is not suitable for us
    if (buffer != nullptr) {
        buffer->SetData(data);
    }
}

} // namespace ERNEST
