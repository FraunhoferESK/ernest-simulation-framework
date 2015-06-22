# Copyright (C) 2014 Fraunhofer Institute for Embedded Systems and
# Communication Technologies ESK
# 
# This file is part of ERNEST.
# 
# ERNEST is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# ERNEST is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with ERNEST.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 2.8)

project(ERNEST)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

set(ERNEST_BUILD_DOC FALSE CACHE BOOL "TRUE to build generate API documentation")
set(ERNEST_BUILD_LIBRARY TRUE CACHE BOOL "TRUE to build the library")
set(ERNEST_BUILD_TESTS FALSE CACHE BOOL "TRUE to build the test programs")

set(PATH_SYSTEMC_INCLUDE $ENV{SYSTEMC_INCLUDE_PATH} CACHE PATH "Path to the SystemC includes")
set(PATH_XERCES_INCLUDE $ENV{XERCES_INCLUDE_PATH} CACHE PATH "Path to Xerces includes")
set(PATH_BOOST_ROOT $ENV{BOOST_ROOT} CACHE PATH "Path to Boost")
set(PATH_BT1LIB_INCLUDE $ENV{BT1LIB_INCLUDE_PATH} CACHE PATH "Path to BT1 C++ Library includes")

set(PATH_SYSTEMC_LIBRARY $ENV{SYSTEMC_LIBRARY_PATH} CACHE PATH "Path to SystemC.lib")
set(PATH_XERCES_LIBRARY $ENV{XERCES_LIBRARY_PATH} CACHE PATH "Path to Xerces.Lib")
set(PATH_BT1LIB_LIBRARY $ENV{BT1LIB_LIBRARY_PATH} CACHE PATH "Path to bt1lib.lib")

if(ERNEST_BUILD_LIBRARY)
  add_subdirectory(src)
  add_subdirectory(include)
endif()

if(ERNEST_BUILD_DOC)
  add_subdirectory(doc)
endif()

if(ERNEST_BUILD_TESTS)
  add_subdirectory(test)
endif()

# install(FILES license.txt DESTINATION ${INSTALL_MISC_DIR})
# install(FILES readme.txt DESTINATION ${INSTALL_MISC_DIR})
