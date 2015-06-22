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
#ifndef ERNEST_BINARY_TRACE_RECORDER_HEADER
#define ERNEST_BINARY_TRACE_RECORDER_HEADER

#include "trace_recorder.hpp"

namespace ERNEST
{
class BinaryTraceRecorderImpl;

class BinaryTraceRecorder : public ITraceRecorder
{
public:
	BinaryTraceRecorder(const char* path);
    void WriteEvent(const char* name, const char* uri, double timestamp);
    void Save();

    /**
     * Add entry to map model names to event id
     *
     * @param name The model element name
     * @param id The event id for tracing
     */
    void AddEventMapping(const char* name, int id);

private:
    BinaryTraceRecorderImpl* m_impl;
};

}

#endif /* ERNEST_BINARY_TRACE_RECORDER_HEADER */
