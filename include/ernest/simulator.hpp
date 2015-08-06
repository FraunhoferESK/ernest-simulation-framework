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
#ifndef ERNEST_SIMULATOR_HEADER
#define ERNEST_SIMULATOR_HEADER

#include <iostream>
#include <ernest/ernest_addition.hpp>
#include <ernest/time.hpp>
#include "ernest_systemc.hpp"

namespace ERNEST
{

class ITraceRecorder;

/**
 * Main class of the simulation.
 */
class Simulator
{
public:
    /**
     * Initialize the simulation with a model.
     *
     * @param model Model of the system to simulate.
     */
    static void Init(wchar_t const* model);

    /**
     * Sets the duration of the simulation.
     *
     * @param duration Amount of time the simulation should be run.
     * @param unit     Unit of the time given in duration.
     */
    static void SetDuration(Time duration);

    /**
     * Start the simulation.
     */
    static void Start();

    /**
     * Get a pointer to the TraceRecorder used by the simulation.
     * Will return nullptr if no TraceRecorder was set.
     */
    static ITraceRecorder* GetTraceRecorder();

    /**
     * Set the TraceRecorder used by the simulation.
     *
     * @param recorder The new TraceRecorder to be used.
     */
    static void SetTraceRecorder(ITraceRecorder* recorder);

    /**
     * Write logging information.
     *
     * This function should be used in favor of directly writing to stdout.
     *
     * @param message The message to log
     */
    static std::ostream& Log();

    /**
     * Write error information.
     *
     * This function should be used in favor of directly writing to stderr.
     *
     * @param message The message to report an error
     */
    static std::ostream& Err();

    /**
     * Write warning information.
     *
     * This function should be used in favor of directly writing to stdout 
     * to issue a warning.
     *
     * @param message The message to report an error
     */
    static std::ostream& Warning();

    /**
     * Create a timestamp in simulated time.
     */
    static Time TimeStamp();

private:
    /**
     * Disable copy constructor
     */
    Simulator(const Simulator&);

    /**
     * Disable copy assignment operator
     */
    Simulator& operator=(const Simulator&);

    static Time m_duration;
    static wchar_t const* m_model;
    static ITraceRecorder* m_trace_recorder;
};

}

#endif /* ERNEST_SIMULATOR_HEADER */
