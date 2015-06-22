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
#include <string>
#include <sstream>
#include <ernest/version.hpp>

namespace ERNEST
{

int Version::GetMajor()
{
    return ERNEST_API_MAJOR;
}

int Version::GetMinor()
{
    return ERNEST_API_MINOR;
}

int Version::GetPatch()
{
    return ERNEST_API_PATCH;
}

const std::string Version::GetVersion()
{
    std::stringstream ss;
    ss << ERNEST_API_MAJOR
       << "."
       << ERNEST_API_MINOR
       << "."
       << ERNEST_API_PATCH;
    return ss.str();
}

bool Version::IsAtLeast(int major, int minor, int patch)
{
    return (ERNEST_API_MAJOR > major) ||
           (ERNEST_API_MAJOR == major && ERNEST_API_MINOR > minor) ||
           (ERNEST_API_MAJOR == major && ERNEST_API_MINOR == minor && ERNEST_API_PATCH >= patch);
}

}
