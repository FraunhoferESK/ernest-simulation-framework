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

# library
file(GLOB_RECURSE ERNEST_HEADERS *.hpp)
file(GLOB_RECURSE ERNEST_SOURCES *.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(${PATH_SYSTEMC_INCLUDE})
include_directories(${PATH_XERCES_INCLUDE})
include_directories(${PATH_BOOST_ROOT})
include_directories(${PATH_BT1LIB_INCLUDE})

add_library(ernest ${ERNEST_SOURCES})
target_link_libraries(ernest systemc XercesLib bt1lib)

if(WIN32)
  set_target_properties(ernest PROPERTIES COMPILE_FLAGS "/vmg")
  # Rule combining all libraries in one ernest.lib archive
  #add_custom_target(ernestcombined ALL 
  # COMMAND lib.exe /OUT:ernestcombined.lib $<TARGET_FILE:systemc> $<TARGET_FILE:xerces>)
ENDIF(WIN32)

install(TARGETS ernest
        ARCHIVE DESTINATION lib)
