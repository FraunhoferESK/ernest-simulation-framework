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
#ifndef ERNEST_UNIFORM_EXECUTION_SPECIFICATION_HEADER
#define ERNEST_UNIFORM_EXECUTION_SPECIFICATION_HEADER

#include <boost/scoped_ptr.hpp>
#include <ernest/time.hpp>
#include "execution_specification_interface.hpp"

namespace ERNEST
{
class UniformExecutionSpecificationImpl;

class UniformExecutionSpecification: public ExecutionSpecificationInterface
{
public:
    /**
     * Creates an object describing the execution time of a task with
     * uniform distribution.
     *
     * The execution time of task is a random value in the range of
     * execution_time +- range.
     *
     * @param execution_time The base execution time of a task
     * @param variation_range The execution time variation range of the task
     */
    UniformExecutionSpecification(Time execution_time,
                                  Time variation_range);

    ~UniformExecutionSpecification();

    /**
     * Get the execution time of a task
     *
     *@return The execution time of a task
     */
    virtual Time GetExecutionTime();

private:
    boost::scoped_ptr<UniformExecutionSpecificationImpl> m_impl;
};

} // namespace ERNEST

#endif /* ERNEST_UNIFORM_EXECUTION_SPECIFICATION_HEADER */
