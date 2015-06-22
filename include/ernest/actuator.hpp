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
#ifndef ERNEST_ACTUATOR_HEADER
#define ERNEST_ACTUATOR_HEADER

#include "ernest_addition.hpp"
#include "ecu.hpp"
#include "flow_port.hpp"

namespace ERNEST
{
struct TaskContext;

/**
 * This class is the superclass for all Actuators in this framework.
 *
 * It contains:
 *  - Information of Ecu and OS, to which it is attached
 *  - A port for receiving data from other software functions
 *  - A virtual function which can be implemented for data processing algorithm
 *
 * @see SimpleActuator
 */
template <typename DataType, int SamplingPeriod>
SC_MODULE(Actuator)
{
SC_HAS_PROCESS(Actuator);

public:
    /**
     * Constructor
     *
     * @param name The name of the Actuator.
     */
    Actuator(sc_module_name name);

    /**
     * Set the Ecu.
     *
     * This function is required by the Ecu class.
     *
     * @param ecu Pointer to Ecu.
     */
    void set_ecu(Ecu* ecu);

    /**
     * Member which contains the actual flow port data.
     */
    FlowPort<DataType, In> data;

private:
    /**
     * Receives data from the flow port and processes it.
     *
     * Derived classes have to implement this function. This function will be
     * called periodically according to the template parameter SamplingPeriod
     */
    virtual void ProcessReceivedData() = 0;
    TaskContext m_context;
    Ecu* m_ecu;
};

template <typename DataType, int SamplingPeriod>
Actuator<DataType, SamplingPeriod>::Actuator(sc_module_name name) : sc_module(name),
    data("ActuatorData", &m_context), m_ecu(nullptr)
{
    SC_THREAD(ProcessReceivedData);
    data = DataType();
}

template <typename DataType, int SamplingPeriod>
void Actuator<DataType, SamplingPeriod>::set_ecu(Ecu* ecu)
{
    m_ecu = ecu;
    m_context.os = m_ecu->GetService<OsekOS>();
}

} // namespace ERNEST

#endif /* ERNEST_ACTUATOR_HEADER */
