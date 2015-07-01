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
#ifndef ERNEST_CLIENT_SERVER_PORT_HEADER
#define ERNEST_CLIENT_SERVER_PORT_HEADER

#include <boost/function.hpp>
#include "basic_port.hpp"

namespace ERNEST
{

/**
 * Inherit from this class to define a provided interface
 *
 */
class ProvidedInterface
{
};

/**
 * Inherit from this class to define a required interface
 *
 */
class RequiredInterface
{
public:
    void SetProvidedInterface(void* inter)
    {
        m_provided_interface = inter;
    }

private:
    void* m_provided_interface;
};

/**
 * Class used for Client/Server communication via ports
 *
 */
template <class Interface>
class ClientServerPort : public BasicPort<boost::function<void ()> >
{
public:
    ClientServerPort(const char* name, TaskContext* context) :
        BasicPort(name, context), m_interface(this) {}

    template <class RequiredInterface, class ProvidedInterface>
    friend void connect_ports(ClientServerPort<RequiredInterface>& src_port,
                              ClientServerPort<ProvidedInterface>& dst_port);
    void Exec()
    {
        ReadSignal();
        m_data();
    }

    Interface* operator-> ()
    {
        return &m_interface;
    }

    virtual size_t GetDataSize()
    {
        return sizeof(void*);
    }

    Interface* GetInterface()
    {
        return &m_interface;
    }

private:
    /**
     * Disable copy constructor of ClientServerPort class
     *
     */
    ClientServerPort(const ClientServerPort&);

    /**
     * Disable copy assignment of ClientServerPort class
     *
     */
    ClientServerPort& operator=(const ClientServerPort&);

    Interface m_interface;
};

/**
 * Free function to connect Client/Server ports together
 *
 * @tparam RequiredInterface Required interface that inherits from
 *         class RequiredInterface
 * @tparam ProvidedInterface Provided interface that inherits from
 *         class ProvidedInterface
 * @param src_port The source port which will be connected
 * @param dst_port The destination port which will be connected
 */
template <class RequiredInterface, class ProvidedInterface>
void connect_ports(ClientServerPort<RequiredInterface>& src_port,
                   ClientServerPort<ProvidedInterface>& dst_port)
{
    connect_ports( (BasicPort<boost::function<void ()> >& ) src_port,
                   (BasicPort<boost::function<void ()> >&) dst_port);
    src_port->m_provided = dst_port.GetInterface();
}

}

#endif /* ERNEST_CLIENT_SERVER_PORT_HEADER */
