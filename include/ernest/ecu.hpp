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
#ifndef ERNEST_ECU_HEADER
#define ERNEST_ECU_HEADER

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "ernest_systemc.hpp"
#include <map>

namespace ERNEST
{

/**
 * Class defining an ECU in form of a SystemC module.
 */
SC_MODULE(Ecu)
{
public:
    SC_HAS_PROCESS(Ecu);

    /**
      * Constructor for Ecu.
      *
      * @param instname the name of the instance
      */
    Ecu(sc_module_name instname);

    /**
      * Process in the Ecu module.
      */
    void Process(void);

    /**
     * Returns the service assigned to the Ecu.
     *
     * @return Class pointer
     */
    template <class C>
    C* GetService() {
        return (C*) m_services[&typeid(C)];
    }

    /**
     * Adds a new service of class C.
     *
     * @return Class pointer
     */
    template <class C>
    C* AddService() {
        C* service = new C(this);
        m_services[&typeid(C)] = service;
        return service;
    }

    /**
     * Returns the hardware assigned to the Ecu.
     *
     * @return Class pointer
     */
    template <class C>
    C* GetHardware() {
        return (C*) m_hardware[&typeid(C)];
    }

    /**
     * Adds a new hardware of class C.
     *
     * @return Class pointer
     */
    template <class C>
    C* AddHardware() {
        C* hardware = new C("HARDWARE");
        hardware->set_ecu(this);

        m_hardware[&typeid(C)] = hardware;
        return hardware;
    }

private:
    std::map<const std::type_info*, void*> m_services;
    std::map<const std::type_info*, void*> m_hardware;
};

} // namespace ERNEST

#endif /* ERNEST_ECU__HEADER */
