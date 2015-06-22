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
#include <boost/scoped_ptr.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <ernest/time.hpp>
#include <ernest/uniform_execution_specification.hpp>

namespace ERNEST
{
using namespace boost::random;

class UniformExecutionSpecificationImpl
{
public:
    UniformExecutionSpecificationImpl(Time execution_time,
                                      Time variation_range)
    {
        Time min = execution_time - variation_range;
        Time max = execution_time + variation_range;

        m_dist = uniform_int_distribution<int>(static_cast<int>(min.GetMilliseconds()),
                                               static_cast<int>(max.GetMilliseconds()));
    }

    Time GetExecutionTime()
    {
        return milliseconds(m_dist(m_generator));
    }

private:
    uniform_int_distribution<int> m_dist;
    boost::random::mt19937 m_generator;
};

UniformExecutionSpecification::UniformExecutionSpecification(
    Time execution_time, Time variation_range) :
    m_impl(new UniformExecutionSpecificationImpl(execution_time, variation_range))
{
}

/*
 * Empty destructor necessary, because scoped_ptr destructor needs 
 * complete type.
 */
UniformExecutionSpecification::~UniformExecutionSpecification()
{
}

Time UniformExecutionSpecification::GetExecutionTime()
{
    return m_impl->GetExecutionTime();
}

} // namespace ERNEST
