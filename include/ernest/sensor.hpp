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
#ifndef ERNEST_SENSOR_HEADER
#define ERNEST_SENSOR_HEADER

#include "ernest_addition.hpp"
#include "ecu.hpp"
#include "flow_port.hpp"

namespace ERNEST
{
struct TaskContext;

/**
 * This class is the superclass for all Sensors in this framework.
 *
 * It contains:
 *  - Information of Ecu and OS, to which it is attached
 *  - A port, which also generates data, for transmitting data
 *  - A virtual function which can be implemented for data generating algorithm
 *
 * @see SimpleSensor
 */
template <typename SensorData, int SamplingPeriod>
SC_MODULE(Sensor)
{
SC_HAS_PROCESS(Sensor);

public:
    /**
     * Constructor
     *
     * @param name The name of the Sensor.
     */
    Sensor(sc_module_name name);

    /**
     * Set the Ecu.
     *
     * This function is required by the Ecu class.
     *
     * @param ecu Pointer to the Ecu.
     */
    void set_ecu(Ecu* ecu);

    /**
     * Member which contains the actual flow port data.
     */
    FlowPort<SensorData, Out> data;

private:
    /**
     * Processes the sensor data and sends it via the flow port.
     *
     * Derived classes have to implement this function. This function will be
     * called periodically according to the template parameter SamplingPeriod
     */
    virtual void SendData() = 0;
    TaskContext m_context;
    Ecu* m_ecu;
};

template <typename SensorData, int SamplingPeriod>
Sensor<SensorData, SamplingPeriod>::Sensor(sc_module_name name) : sc_module(name),
    data("SensorData", &m_context), m_ecu(nullptr)
{
    SC_THREAD(SendData);
    data = SensorData();
}

template <typename SensorData, int SamplingPeriod>
void Sensor<SensorData, SamplingPeriod>::set_ecu(Ecu* ecu)
{
    m_ecu = ecu;
    m_context.os = m_ecu->GetService<OsekOS>();
}

} // namespace ERNEST

#endif /* ERNEST_SENSOR_HEADER */
