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
#ifndef ERNEST_NORMAL_EXECUTION_SPECIFICATION_HEADER
#define ERNEST_NORMAL_EXECUTION_SPECIFICATION_HEADER

#include <boost/scoped_ptr.hpp>
#include <ernest/time.hpp>
#include "execution_specification_interface.hpp"

namespace ERNEST{
class NormalExecutionSpecificationImpl;

class NormalExecutionSpecification: public ExecutionSpecificationInterface
{
public:
    /**
     * Creates an object describing the execution time of a task based
     * on a normal / gaussian distribution
     *
     * The distribution has two parameters which is the mean and the
     * variance
     *
     * @param mean_execution The mean execution time of task
     * @param variance The variance of the task execution time
     */
    NormalExecutionSpecification(Time mean_execution, Time variance);

    ~NormalExecutionSpecification();

    Time GetExecutionTime();

private:
    boost::scoped_ptr<NormalExecutionSpecificationImpl> m_impl;
};

} // namespace ERNEST

#endif /* ERNEST_NORMAL_EXECUTION_SPECIFICATION_HEADER */
