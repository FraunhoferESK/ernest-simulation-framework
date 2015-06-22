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
#include <ernest/binary_recorder.hpp>
#include <map>
#include <string>
#include <ot1lib.hpp>
#include <ernest/simulator.hpp>

namespace ERNEST
{
typedef std::map<std::string, unsigned int> ElementMap;

class BinaryTraceRecorderImpl
{
public:
	BinaryTraceRecorderImpl(const char* path);
    void WriteEvent(const char* name, const char* uri, double timestamp);
    void Save();
    void AddEventMapping(const char* name, int id);

private:
    const char* m_path;
    OT1::File m_file;
    OT1::EventBuffer* m_event_buffer;
    ElementMap m_element_map;
    unsigned int m_max_id;
};


BinaryTraceRecorderImpl::BinaryTraceRecorderImpl(const char* path) :
	m_path(path), m_file(path), m_max_id(0)
{
    m_event_buffer = m_file.create_event_buffer(OT1::TAE, 0, 50);
}

void BinaryTraceRecorderImpl::WriteEvent(const char* name,
                                      const char* uri,
                                      double timestamp)
{
    unsigned int id;

    if (m_element_map.find(uri) != m_element_map.end()) {
        id = m_element_map.find(uri)->second;
        m_event_buffer->write_event(0, id, (uint64_t) timestamp);
    } else {
        Simulator::Log() << "OT1 Trace mapping for: '" << name << "' not found." << std::endl;
    }

}

void BinaryTraceRecorderImpl::Save()
{
    m_event_buffer->flush();
}

void BinaryTraceRecorderImpl::AddEventMapping(const char* name, int id)
{
    m_element_map.insert(std::make_pair(name, id));
}

BinaryTraceRecorder::BinaryTraceRecorder(const char* path)
{
    m_impl = new BinaryTraceRecorderImpl(path);
}
    
void BinaryTraceRecorder::WriteEvent(const char* name,
                                  const char* uri,
                                  double timestamp)
{
    m_impl->WriteEvent(name, uri, timestamp);
}

void BinaryTraceRecorder::Save()
{
    m_impl->Save();
}

void BinaryTraceRecorder::AddEventMapping(const char* name, int id)
{
    m_impl->AddEventMapping(name, id);
}

} // namespace ERNEST
