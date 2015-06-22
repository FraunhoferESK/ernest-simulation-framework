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
#ifndef ERNEST_SIMPLE_SENSOR_HEADER
#define ERNEST_SIMPLE_SENSOR_HEADER

#include "ernest_systemc.hpp"
#include "sensor.hpp"

namespace ERNEST
{

/**
 * This class is a simple sensor which generates monotonically increasing 
 * data.
 *
 * The class derives from the Sensor class and implements a simple sensor 
 * for testing purpose. It generates monotonically increasing data by 
 * applying the increment operator (++) to the data specified by SensorData.
 */
template <typename SensorData, int SamplingPeriod>
struct SimpleSensor : public Sensor<SensorData, SamplingPeriod>
{
public:
    /**
     * Constructor.
     *
     * @param name The name of the SimpleSensor
     */
    SimpleSensor(sc_module_name name);

private:
    /**
     * Derives from the Sensor class virtual function. It processes sensor
     * data
     *
     * It generates monotonically increasing data by applying the increment 
     * operator (++).
     */
    void SendData();

}; // struct SimpleSensor

template <typename SensorData, int SamplingPeriod>
SimpleSensor<SensorData, SamplingPeriod>::SimpleSensor(sc_module_name name) :
    Sensor<SensorData, SamplingPeriod>(name)
{

}

template <typename SensorData, int SamplingPeriod>
void SimpleSensor<SensorData, SamplingPeriod>::SendData()
{
    while(true) {
        this->data.Push();
        this->data++;
        wait(SamplingPeriod, SC_MS);
    }
}

} // namespace ERNEST

#endif /* ERNEST_SENSOR_HEADER */
