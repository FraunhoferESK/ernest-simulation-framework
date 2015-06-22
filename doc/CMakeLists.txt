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

# Building and installing of ERNEST API Documentation
# Variables:
# DOXYGEN_INPUT_DIR
# DOXYGEN_OUTPUT_DIR
# DOXYGEN_CONFIGURED_INPUT

find_package(Doxygen REQUIRED)

set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR})
set(DOXYGEN_OUTPUT_DIR ${PROJECT_BINARY_DIR}/doc)

# configure the doxyfile by replacing the variables
set(DOXYGEN_CONFIGURED_INPUT ${DOXYGEN_OUTPUT_DIR}/doxyfile)
configure_file(${DOXYGEN_INPUT_DIR}/doc/doxyfile.in ${DOXYGEN_CONFIGURED_INPUT} @ONLY)

# target setup
add_custom_target(doc ALL
                  COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
                  COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIGURED_INPUT}
                  COMMAND ${CMAKE_COMMAND} -E echo "Done."
                  WORKING_DIRECTORY ${DOXYGEN_INPUT_DIR})

# copy some files for documentation
# configure_file(${DOXYGEN_INPUT_DIR}/doc/esk_logo.gif ${DOXYGEN_OUTPUT_DIR}/esk_logo.gif COPYONLY)

# install rules
install(DIRECTORY ${DOXYGEN_OUTPUT_DIR}/html
        DESTINATION doc
        COMPONENT doc)
