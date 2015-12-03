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

#ifndef ERNEST_PLUGIN_MANAGER_HEADER
#define ERNEST_PLUGIN_MANAGER_HEADER

#include <string>
#include <map>

namespace ERNEST
{

class IOsekService;
  
class PluginManager
{
public:
    static void RegisterOsekService(std::string id, IOsekService* service);
    static IOsekService* CreateOsekService(std::string id);


private:
    static std::map<const std::string, IOsekService*> m_osekservice;
};
  
}  // ERNEST

#endif /* ERNEST_PLUGIN_MANAGER_HEADER */
