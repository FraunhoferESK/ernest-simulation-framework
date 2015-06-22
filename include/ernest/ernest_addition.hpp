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
#ifndef ERNEST_ERNEST_ADDITION_HEADER
#define ERNEST_ERNEST_ADDITION_HEADER

#include <cstddef>

#ifdef __GNUC__
#define DEPRECATED(func) __attribute__ ((deprecated)) func
#elif defined(_MSC_VER)
#define DEPRECATED(func) __declspec(deprecated) func
#endif

namespace ERNEST
{

typedef unsigned int PortId;
typedef unsigned int EcuId;

/**
 * Definition of SignalData
 */
struct SignalData {
    std::size_t size;
    void* dataPtr;
};

/**
 * Enumeration created for the different Communication methods
 */
enum Communication {
    Local,
    Simple,
    Can
};

static const int nullptr = 0;

} // namespace ERNEST

#endif /* ERNEST_ERNEST_ADDITION_HEADER */
