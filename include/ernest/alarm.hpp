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
#ifndef ERNEST_ALARM_HEADER
#define ERNEST_ALARM_HEADER

#include "osek_service.hpp"
#include "alarm_listener.hpp"
#include "time.hpp"


namespace ERNEST
{

//
// Forward declarations
//
class OsekOS;
class TimerImpl;
struct Alarm;

/**
 * This class provides timer functionality. It allows clients which
 * implement \ref AlarmListener to be notified when the timer expires.
 */
class Timer : public IOsekService
{
public:
	Timer();

    /**
     * During update expired alarms are checked and the registered
     * clients (\ref AlarmListener) are notified.
     */
    void Update(OsekOS* osekos);

    /**
     * Registers an \ref AlarmListener client to be notified when the
     * absolute alarm expires. An absolute alarm is relative to the
     * time of the method invocation.
     *
     * @param listener Pointer to the client which will be notified
     * @param start The expiration time, relative to the current time
     * @param cycle The cycle time for a periodic alarm. Non-periodic if cycle equals to zero.
     */
    void SetAbsAlarm(AlarmListener* listener, int id, Time start, Time cycle);

    /**
     * Registers an \ref AlarmListener client to be notified when the
     * relative alarm expires. A relative alarm is relative to the
     * time of the original alarm expiration.
     *
     * @param listener Pointer to the client which will be notified
     * @param start The expiration time, relative to the original expiration time
     * @param cycle The cycle time for a periodic alarm. Non-periodic if cycle equals to zero.
     */
    void SetRelAlarm(AlarmListener* listener, int id, Time start, Time cycle);

    /**
     * Delete the alarm.
     *
     * @param alarm Reference to the alarm to be removed.
     */
    void DeleteAlarm(Alarm* listener);

private:
    /**
     * Disable copy constructor.
     */
    Timer(const Timer&);

    /**
     * Disable copy assignment operator.
     */
    Timer& operator=(const Timer&);

    /**
     * Retrieves an \ref Alarm object of a given \ref
     * AlarmListener. If an existing \ref Alarm object is already
     * used, it will be reused. If no \ref Alarm object exists for a
     * \ref AlarmListener, a new one will be allocated.
     *
     * @param listener Pointer to the client, for which the Alarm
     *                 object should be retrieved
     * @retpar Pointer to the Alarm object
     */
    Alarm* GetAlarm(AlarmListener* listener);

    TimerImpl* m_impl;
};

} // namespace ERNEST

#endif /* ERNEST_ALARM_HEADER */
