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
#ifndef ERNEST_SIMPLE_ACTUATOR_HEADER
#define ERNEST_SIMPLE_ACTUATOR_HEADER

#include "ernest_systemc.hpp"
#include "actuator.hpp"

namespace ERNEST
{

/**
 * This class is a simple actuator which displays the received data.
 *
 * The class derives from the Actuator class and implements a simple actuator
 * for testing purpose. It displays received data in ProcessReceivedData.
 */
template <typename DataType, int SamplingPeriod>
struct SimpleActuator : public Actuator<DataType, SamplingPeriod>
{
public:
    /**
     * Constructor.
     *
     * @param name The name of the SimpleActuator
     */
    SimpleActuator(sc_module_name name);

private:
    /**
     * Derives from the Actuator class virtual function. It receives data
     * and does further processing
     *
     * It simply displays data it receives from another software function. 
     */
    void ProcessReceivedData();

}; // struct SimpleActuator

template <typename DataType, int SamplingPeriod>
SimpleActuator<DataType, SamplingPeriod>::SimpleActuator(sc_module_name name) :
    Actuator<DataType, SamplingPeriod>(name)
{

}

template <typename DataType, int SamplingPeriod>
void SimpleActuator<DataType, SamplingPeriod>::ProcessReceivedData()
{
    while(true) {
        this->data.Pull();
        cout << "              actuator processes data: " << this->data << endl;
        wait(SamplingPeriod, SC_MS);
    } 
}

} // namespace ERNEST

#endif /* ERNEST_SIMPLE_ACTUATOR_HEADER */
