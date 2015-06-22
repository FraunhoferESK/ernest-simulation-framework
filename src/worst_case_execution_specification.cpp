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
#include <ernest/time.hpp>
#include <ernest/worst_case_execution_specification.hpp>

namespace ERNEST
{

class WorstCaseExecutionSpecificationImpl
{
public:
    WorstCaseExecutionSpecificationImpl(Time execution_time) : m_execution_time(execution_time)
    {
    }

    Time GetExecutionTime()
    {
        return m_execution_time;
    }

private:
    Time m_execution_time;
};

WorstCaseExecutionSpecification::WorstCaseExecutionSpecification(
    Time execution_time) : m_impl(new WorstCaseExecutionSpecificationImpl(execution_time))
{

}

/*
 * Empty destructor necessary, because scoped_ptr destructor needs 
 * complete type.
 */
WorstCaseExecutionSpecification::~WorstCaseExecutionSpecification()
{
}

Time WorstCaseExecutionSpecification::GetExecutionTime()
{
    return m_impl->GetExecutionTime();
}

} // namespace ERNEST
