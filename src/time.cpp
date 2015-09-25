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
#include <ernest/time.hpp>

namespace ERNEST {

class TimeImpl
{
public:
	TimeImpl(double amount, TimeUnit unit)
	{
		switch(unit)
		{
			case Seconds:
				m_milliseconds = amount * 1000;
				break;

			case Milliseconds:
				m_milliseconds = amount;
				break;

			case Microseconds:
				m_milliseconds = amount / 1000;
				break;
		}
	}

	double GetSeconds() {
		return m_milliseconds / 1000;
	}

	double GetMilliseconds() {
		return m_milliseconds;
	}

	double GetMicroseconds() {
		return m_milliseconds * 1000;
	}

	void SetMilliseconds(double ms) {
		m_milliseconds = ms;
	}

private:
	double m_milliseconds;
};

Time::Time() : m_impl(new TimeImpl(0, Milliseconds))
{
}

Time::Time(int t) : m_impl(new TimeImpl(0, Milliseconds))
{
}
  
Time::Time(double amount, TimeUnit unit) : m_impl(new TimeImpl(amount, unit))
{
}

double Time::GetSeconds() const
{
	return m_impl->GetSeconds();
}

double Time::GetMilliseconds() const
{
	return m_impl->GetMilliseconds();
}

double Time::GetMicroseconds() const
{
	return m_impl->GetMicroseconds();
}

Time Time::operator+(Time& rhs)
{
	double sum = GetMilliseconds() + rhs.GetMilliseconds();
	return milliseconds(sum);
}

Time Time::operator-(Time& rhs)
{
	double difference = GetMilliseconds() - rhs.GetMilliseconds();
	return milliseconds(difference);
}

bool Time::operator<(Time& rhs)
{
    return GetMilliseconds() < rhs.GetMilliseconds();
}

bool Time::operator==(const Time& rhs) const
{
	return (GetMilliseconds() == rhs.GetMilliseconds());
}

bool Time::operator!=(const Time& rhs) const
{
	return !(*this==rhs);
}

} // namespace ERNEST
