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
#ifndef ERNEST_FLOW_PORT_HEADER
#define ERNEST_FLOW_PORT_HEADER

#include <string>
#include <queue>
#include "ernest_systemc.hpp"
#include "basic_port.hpp"
#include "simulator.hpp"
#include "trace_recorder.hpp"
#include "ernest_addition.hpp"

namespace ERNEST
{

/**
 * Enum created for the different Port types
 */
enum PortType {
    In,
    Out,
    InOut
};

template <class DataType, PortType P>
class FlowPort : public BasicPort<DataType>
{
public:
    /**
     * Constructor for FlowPort.
     *
     * @param name of the FlowPort
     * @param context as TaskContext
     * @param name of the FlowPort
     */
    FlowPort(const char* name, TaskContext *context, const char* uri = nullptr) :
        BasicPort<DataType>(name, context),
        m_uri(uri)
    {
        if (m_uri != nullptr) {
            m_is_tracing = true;
            m_recorder = Simulator::GetTraceRecorder();
        } else {
            m_is_tracing = false;
        }
    }

    /**
     * Destructor for FlowPort.
     */
    virtual ~FlowPort(void)
    {
    }

    /**
     * Send signal via the Flow Port.
     */
    void Push()
    {
        assert(P == Out || P == InOut);
        if (m_is_tracing) {
            sc_time ts = sc_time_stamp();
            m_recorder->WriteEvent(BasicPort<DataType>::m_name, m_uri, ts.to_double());
        }
        this->SendSignal();
    }

    /**
     * Read signal from the Flow Port.
     */
    void Pull()
    {
        assert(P == In || P == InOut);
        if (m_is_tracing) {
            sc_time ts = sc_time_stamp();
            m_recorder->WriteEvent(BasicPort<DataType>::m_name, m_uri, ts.to_double());
        }
        this->ReadSignal();
    }

    FlowPort& operator= (DataType const& rhs)
    {
        this->m_data = rhs;
        return *this;
    }

    FlowPort& operator= (FlowPort const& rhs)
    {
        this->m_data = rhs.m_data;
        return *this;
    }

    FlowPort& operator++ ()
    {
        ++(this->m_data);
        return *this;
    }

    const FlowPort& operator++ (int)
    {
        this->m_data++;
        return *this;
    }

    operator DataType() const
    {
        return this->m_data;
    }

    /**
     * Get the size of the data type.
     *
     * @return size_t unsigned integer
     */
    virtual size_t GetDataSize()
    {
        return sizeof(DataType);
    }

private:
    FlowPort(const FlowPort&);
    const char* m_uri;
    bool m_is_tracing;
    ITraceRecorder* m_recorder;
};

} // namespace ERNEST

#endif /* ERNEST_FLOW_PORT_HEADER */
