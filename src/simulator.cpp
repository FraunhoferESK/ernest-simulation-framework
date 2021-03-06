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
#include <iostream>
#include <ernest/simulator.hpp>
#include <ernest/trace_recorder.hpp>
#include <ernest/ernest_addition.hpp>

namespace ERNEST
{

ITraceRecorder* Simulator::m_trace_recorder = nullptr;
wchar_t const* Simulator::m_model = L"undefined";
Time Simulator::m_duration = seconds(0);
Time Simulator::m_time_resolution = Time(1.0, Milliseconds);

ITraceRecorder* Simulator::GetTraceRecorder()
{
    return m_trace_recorder;
}

void Simulator::SetTraceRecorder(ITraceRecorder* recorder)
{
    if (m_trace_recorder != nullptr) {
        delete m_trace_recorder;
    }

    m_trace_recorder = recorder;
}

void Simulator::Init(wchar_t const* model)
{
    m_model = model;
    Simulator::SetTimeResolution(Time(1.0, Milliseconds));
}

void Simulator::SetDuration(Time duration)
{
    m_duration = duration;
}

void Simulator::SetTimeResolution(const Time& resolution)
{
	m_time_resolution = resolution;
	sc_set_time_resolution(resolution.GetMilliseconds(), SC_MS);
}

const Time& Simulator::GetTimeResolution()
{
	return m_time_resolution;
}

void Simulator::Start()
{
    Simulator::Log() << "Starting Simulation." << std:: endl;

    sc_start(sc_time(m_duration.GetMilliseconds(), SC_MS));
    GetTraceRecorder()->Save();

    Simulator::Log() << "Simulation finished." << std:: endl;
}

std::ostream& Simulator::Log()
{
    std::cout << sc_time_stamp().to_double() << " [ERNEST][INFO]: ";
    return std::cout;
}

std::ostream& Simulator::Err()
{
    std::cerr << sc_time_stamp().to_double() << " [ERNEST][ERROR]: ";
    return std::cerr;
}

std::ostream& Simulator::Warning()
{
    std::cout << sc_time_stamp().to_double() << " [ERNEST][WARNING]: ";
    return std::cout;
}

Time Simulator::TimeStamp()
{
    sc_time ts = sc_time_stamp();
    return Time(ts.to_double(), Milliseconds);
}

void Simulator::Wait(const Time& t)
{
	wait(sc_time(t.GetMilliseconds(), SC_MS));
}

} // namespace ERNEST
