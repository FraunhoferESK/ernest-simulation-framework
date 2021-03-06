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
#include <boost/random/normal_distribution.hpp>
#include <ernest/normal_execution_specification.hpp>
#include <ernest/time.hpp>

namespace ERNEST {
using namespace boost::random;

class NormalExecutionSpecificationImpl
{
public:
    NormalExecutionSpecificationImpl(Time mean_execution, Time variance)
    {
        m_dist = normal_distribution<double>(mean_execution.GetMilliseconds(),
                                             variance.GetMilliseconds());
    }

    Time GetExecutionTime()
    {
        return milliseconds(m_dist(m_generator));
    }

private:
    normal_distribution<double> m_dist;
    mt19937 m_generator;
};

NormalExecutionSpecification::NormalExecutionSpecification(Time mean_execution, Time variance) :
    m_impl(new NormalExecutionSpecificationImpl(mean_execution, variance))
{
}

/*
 * Empty destructor necessary, because scoped_ptr destructor needs 
 * complete type.
 */
NormalExecutionSpecification::~NormalExecutionSpecification()
{
}

Time NormalExecutionSpecification::GetExecutionTime()
{
    return m_impl->GetExecutionTime();
}

} // namespace ERNEST
