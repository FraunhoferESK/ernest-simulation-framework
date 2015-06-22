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
#ifndef ERNEST_TEST_INTERFACE_HEADER
#define ERNEST_TEST_INTERFACE_HEADER

#include <iostream>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <ernest/software_function.hpp>

namespace ERNEST
{

class TestInterface_Provided : public ProvidedInterface
{
public:
    TestInterface_Provided(ClientServerPort<TestInterface_Provided> *port) : m_port(port) {}

    void foo(int arg)
    {
        std::cout << sc_time_stamp()
                  << ": Server received call: foo("
                  << arg
                  << ")"
                  << std::endl;
    }

    void bar(float arg1, float arg2)
    {
        std::cout << sc_time_stamp()
                  << ": Server received call: bar("
                  << arg1
                  << ", "
                  << arg2
                  << ")"
                  << std::endl;
    }
private:
    ClientServerPort<TestInterface_Provided> *m_port;
};

class TestInterface_Required : public RequiredInterface
{
public:
    TestInterface_Required(ClientServerPort<TestInterface_Required> *port)
        : m_port(port) {}

    void foo(int arg)
    {
        boost::function<void ()> f = boost::bind(&TestInterface_Provided::foo,
                                     m_provided,
                                     arg);
        m_port->SendSignalData(f);
    }

    void bar(float arg1, float arg2)
    {
        boost::function<void ()> f = boost::bind(&TestInterface_Provided::bar,
                                     m_provided,
                                     arg1,
                                     arg2);
        m_port->SendSignalData(f);
    }

    TestInterface_Provided *m_provided;

private:
    ClientServerPort<TestInterface_Required> *m_port;
};

}

#endif /* TEST_INTERFACE_HPP */
