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
#ifndef ERNEST_BASIC_PORT_HEADER
#define ERNEST_BASIC_PORT_HEADER

#include "ernest_addition.hpp"
#include "signal.hpp"
#include "osek_os.hpp"
#include "runtime_environment.hpp"
#include "simulator.hpp"

namespace ERNEST
{
template <class DataType> class BasicPort;

template <class DataType>
void connect_ports(BasicPort<DataType>& src_port, BasicPort<DataType>& dst_port);

/**
 * Class implementing a BasicPort.
 */
template <class DataType>
class BasicPort
{
public:
    friend void connect_ports<DataType>(BasicPort<DataType>& src_port,
                                        BasicPort<DataType>& dst_port);

    typedef DataType data_type;

    /**
     * BasicPort exchanges data with other ports.
     *
     * @param context is the context of a task
     */
    BasicPort(const char* name, TaskContext* context) :
        m_signal_id(nullptr), m_is_bound(false), m_context(context), m_name(name), m_error_logged(false)
    {
    }

    virtual ~BasicPort() {}


    /**
     * Set the signal id.
     *
     * @param signal_id represents the signal id which should be bound to the port.
     */
    void SetSignalId(SignalId signal_id)
    {
        if (!m_is_bound) {
            m_signal_id = signal_id;
            m_is_bound = true;
        } else {
            Simulator::Log() << "Attempt to rebind signal: " << signal_id << " on: " << m_name << std::endl;
        }
    }

    /**
     * Get back the signal id.
     *
     * @return The signal id which is bound to the port.
     */
    SignalId GetSignalId()
    {
        return m_signal_id;
    }

    /**
     * Checks, if a port is bound to a signal.
     *
     * @return true, if port is bound - otherwise false.
     */
    bool IsBound()
    {
        return m_is_bound;
    }

    /**
     * Function used for explicit invocations (send).
     */
    void SendSignal()
    {
        if (m_is_bound) {
            m_context->os->GetRuntimeEnvironment()->SendSignal(m_signal_id, m_data);
        } else {
            if (m_error_logged == false) {
                Simulator::Err() << "Port: " << m_name << " not bound to signal: " << m_signal_id << std::endl;
                m_error_logged = true;
            }
        }
    }

    /**
     * Function for sending data.
     *
     * @param data to be sent via this port.
     */
    void SendSignalData(DataType data)
    {
        m_data = data;
        SendSignal();
    }

    /**
     * Function used for explicit invocations (read).
     */
    void ReadSignal()
    {
        if (m_is_bound) {
            m_context->os->GetRuntimeEnvironment()->ReadSignal(m_signal_id, m_data);
        } else {
            if (m_error_logged == false) {
                Simulator::Err() << "Port: " << m_name << " not bound to signal: " << m_signal_id << std::endl;
                m_error_logged = true;
            }
        }
    }

    /**
     * Function to read the data arriving at the port.
     *
     * @param data read from port.
     */
    void ReadSignalData(DataType *data)
    {
        ReadSignal();
        data = &m_data;
    }

    virtual size_t GetDataSize() = 0;

protected:
    SignalId m_signal_id;
    bool m_is_bound;
    TaskContext* m_context;
    DataType m_data;
    const char* m_name;

private:
    BasicPort(const BasicPort&);
    BasicPort& operator=(const BasicPort&);
    bool m_error_logged;
};

/**
 * Connects two basic ports.
 *
 * @param src_port source port.
 * @param dst_port target port.
 */
template <class DataType>
void connect_ports(BasicPort<DataType>& src_port,
                   BasicPort<DataType>& dst_port)
{
    SignalId new_signal_id;

    if (src_port.IsBound()) {
        new_signal_id = src_port.GetSignalId();
    } else {
        new_signal_id = next_signal();
        src_port.SetSignalId(new_signal_id);
    }

    dst_port.SetSignalId(new_signal_id);

    OsekOS *src_os = src_port.m_context->os;
    OsekOS *dst_os = dst_port.m_context->os;

    if (src_os == dst_os) {
    	src_os->GetRuntimeEnvironment()->AddRoutingEntry<DataType>(new_signal_id,
                Local,
                src_port.m_context);
    } else {
        if(src_os->GetEcu()->GetHardware<CanBusInterface>() != nullptr &&
                dst_os->GetEcu()->GetHardware<CanBusInterface>() != nullptr) {
            src_os->GetRuntimeEnvironment()->AddRoutingEntry<DataType>(new_signal_id,
                    Can,
                    src_port.m_context);
            dst_os->GetRuntimeEnvironment()->AddRoutingEntry<DataType>(new_signal_id,
                    Can, src_port.m_context);
        } else if(src_os->GetEcu()->GetHardware<SimpleBusInterface>() != nullptr &&
                  src_os->GetEcu()->GetHardware<SimpleBusInterface>() != nullptr) {
            src_os->GetRuntimeEnvironment()->AddRoutingEntry<DataType>(new_signal_id,
                    Simple,
                    src_port.m_context);
            dst_os->GetRuntimeEnvironment()->AddRoutingEntry<DataType>(new_signal_id,
                    Simple,
                    src_port.m_context);
        } else {
            cout << "ERROR: " << src_os->GetEcu() <<
                 " and " << src_os->GetEcu() <<
                 " have no common bus interface!" << endl;
        }
    }
}

} // namespace ERNEST

#endif  /* ERNEST_BASIC_PORT_HEADER */
