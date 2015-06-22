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
#ifndef ERNEST_SWF_B_HEADER
#define ERNEST_SWF_B_HEADER

#include <ernest/software_function.hpp>
#include <ernest/flow_port.hpp>

using namespace ERNEST;

/**
 * A software function used in test cases.
 * The function has only incoming flow ports.
 */
class SwfB : public SoftwareFunction
{
public:
    /**
     * Constructor.
     *
     * @param context TaskContext of this software function.
     */
    SwfB(TaskContext* context);

    /**
     * Run this software function.
     */
    void Exec();

    /**
     * Pull all in flow ports.
     */
    void PullPorts();

    /**
     * Push all out flow ports.
     */
    void PushPorts();

    /**
     * Incoming flow ports.
     */
    FlowPort<int, In> counter;
};

#endif /* ERNEST_SWF_B_HEADER */
