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
#ifndef ERNEST_IOSEK_SERVICE_HEADER
#define ERNEST_IOSEK_SERVICE_HEADER

namespace ERNEST
{

class OsekOS;


/**
 * Interface class that every service used by the OSEK OS has to implement
 */
class IOsekService
{
public:
    virtual ~IOsekService() {};

	/**
	 * Update function which is regularly called by the OSEK OS
     * 
     * @param osekos Pointer to the OsekOS calling the Update function
	 */
	virtual void Update(OsekOS* osekos) = 0;

};

} // namespace ERNEST

#endif /* ERNEST_IOSEK_SERVICE_HEADER */
