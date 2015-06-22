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
#ifndef ERNEST_TRACE_RECORDER_HEADER
#define ERNEST_TRACE_RECORDER_HEADER

namespace ERNEST
{

/**
 * Implement this interface to write a custom trace recorder
 */
class ITraceRecorder
{
public:
    /**
     * Write an event into the trace file
     *
     * @param name Name of the model element 
     * @param uri URI of the model element
     * @param timestamp Event timestamp
     */
    virtual void WriteEvent(const char* name,
                            const char* uri,
                            double timestamp) = 0;

    /**
     * Write the trace to disk
     */
    virtual void Save() = 0;

    virtual ~ITraceRecorder() {}
};

}

#endif /* ERNEST_TRACE_RECORDER_HEADER */
