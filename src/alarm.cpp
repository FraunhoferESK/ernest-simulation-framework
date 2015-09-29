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
#include <algorithm>
#include <map>
#include <ernest/ernest_systemc.hpp>
#include <ernest/alarm.hpp>
#include <ernest/time.hpp>

namespace ERNEST
{

struct Alarm
{
    AlarmListener* listener;
    sc_time start;
    sc_time cycle;
    sc_time next_activation;
    int id;
    bool active;
};

class TimerImpl
{
public:
	TimerImpl() : m_last_ts(0.0, SC_MS) {}

	void Update()
	{
	    AlarmMap::iterator it;
	    sc_time delta = sc_time_stamp() - m_last_ts;

	    for (it = m_alarm_objects.begin(); it != m_alarm_objects.end(); ++it) {
	        Alarm* alarm = it->second;
	        if (alarm->active) {
	            // Timer expired?
	            if (alarm->next_activation <= delta) {
	                // Periodic timer?
	                if (alarm->cycle == SC_ZERO_TIME) {
	                    alarm->active = false;
	                } else {
	                    alarm->next_activation = alarm->cycle;
	                }

	                // Notify the client
	                alarm->listener->Notify(alarm->id);

	            } else {
	                // Decrease active timer
	                alarm->next_activation -= delta;
	            }
	        }
	    }

	    m_last_ts = sc_time_stamp();
	}

	void SetAbsAlarm(AlarmListener* listener, int id, Time start, Time cycle)
	{
	    Alarm* alarm = GetAlarm(listener);

	    alarm->cycle = sc_time(cycle.GetMilliseconds(), SC_MS);
	    alarm->next_activation = sc_time(start.GetMilliseconds(), SC_MS);
	}

	void DeleteAlarm(AlarmListener* listener)
	{
	    m_alarm_objects.erase(listener);
	}

	Alarm* GetAlarm(AlarmListener* listener)
	{
	    AlarmMap::iterator it = m_alarm_objects.find(listener);

	    if (it != m_alarm_objects.end())
	    {
	        return it->second;
	    }

	    Alarm* alarm = new Alarm();
	    alarm->active = false;
	    alarm->listener = listener;

	    m_alarm_objects.insert(std::pair<AlarmListener*, Alarm*>(listener, alarm));
	    return alarm;
	}

private:
    typedef std::map<AlarmListener*, Alarm*> AlarmMap;
    AlarmMap m_alarm_objects;
    sc_time m_last_ts;
};

Timer::Timer() : m_impl(new TimerImpl())
{
}

void Timer::Update()
{
	m_impl->Update();
}

void Timer::SetAbsAlarm(AlarmListener* listener, int id, Time start, Time cycle)
{
    m_impl->SetAbsAlarm(listener, id, start, cycle);
}

void Timer::SetRelAlarm(AlarmListener* listener, int id, Time start, Time cycle)
{
    Alarm* alarm = GetAlarm(listener);

    alarm->active = true;
    alarm->start = sc_time(start.GetMilliseconds(), SC_MS);
    alarm->cycle = sc_time(cycle.GetMilliseconds(), SC_MS);
    alarm->next_activation = alarm->cycle + alarm->start;
    alarm->id = id;
}

void Timer::DeleteAlarm(AlarmListener* listener)
{
    m_impl->DeleteAlarm(listener);
}

Alarm* Timer::GetAlarm(AlarmListener* listener)
{
    return m_impl->GetAlarm(listener);
}

} // namespace ERNEST
