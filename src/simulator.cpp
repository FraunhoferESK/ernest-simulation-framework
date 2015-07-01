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
Time  Simulator::m_duration = seconds(0);

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
    sc_set_time_resolution(1.0, SC_MS);
}

void Simulator::SetDuration(Time duration)
{
    m_duration = duration;
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
    std::cout << "[ERNEST][LOG]: ";
    return std::cout;
}

std::ostream& Simulator::Err()
{
    std::cerr << "[ERNEST][ERR]: ";
    return std::cerr;
}

} // namespace ERNEST
