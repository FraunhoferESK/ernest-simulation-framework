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
#ifndef ERNEST_TIME_HEADER
#define ERNEST_TIME_HEADER

namespace ERNEST {

enum TimeUnit {
	Seconds,
	Milliseconds,
	Microseconds,
};

class TimeImpl;

/**
 * Class for describing time quantities
 *
 * The time class is used to describe time quantities within the framework.
 * This class is not intended to be derived.
 */
class Time {
public:
    /**
     * Default constructor for Time
     */
    Time();

    /**
     * Allow casting integer to time
     */
    Time(int t);

	/**
	 * Construct a time object
	 *
	 * @param amount The amount in time units
	 * @param unit The time unit for amount
	 */
	Time(double amount, TimeUnit unit);

	/**
	 * Get time in seconds
	 *
	 * @returns The time in seconds
	 */
	double GetSeconds() const;

	/**
	 * Get time in milliseconds
	 *
	 * @returns The time in milliseconds
	 */
	double GetMilliseconds() const;

	/**
	 * Get time in microseconds
	 *
	 * @returns The time in microseconds
	 */
	double GetMicroseconds() const;

	Time operator+(Time& rhs);

	Time operator-(Time& rhs);

    bool operator<(Time& rhs);

    bool operator==(const Time& rhs) const;
    bool operator!=(const Time& rhs) const;

private:
	TimeImpl* m_impl;
};

/**
 * Convenience function creating a time object for seconds
 *
 * @param amount The amount in seconds
 */
inline Time seconds(double amount) {
	return Time(amount, Seconds);
}

/**
 * Convenience function creating a time object for milliseconds
 *
 * @param amount The amount in milliseconds
 */
inline Time milliseconds(double amount) {
	return Time(amount, Milliseconds);
}

/**
 * Convenience function creating a time object for microseconds
 *
 * @param amount The amount in microseconds
 */
inline Time microseconds(double amount) {
	return Time(amount, Microseconds);
}

} // namespace ERNEST

#endif /* ERNEST_TIME_HEADER */
