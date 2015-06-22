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

include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(${PATH_SYSTEMC_INCLUDE})
include_directories(${PATH_XERCES_INCLUDE})
include_directories(${PATH_BOOST_ROOT})
include_directories(${PATH_BT1LIB_INCLUDE})

link_directories(${PATH_SYSTEMC_LIBRARY})
link_directories(${PATH_XERCES_LIBRARY})
link_directories(${PATH_BT1LIB_LIBRARY})

# sensor test
add_executable(sensor_actuator_test sensor_actuator_test.cpp
                              swf_sensor_actuator.cpp)
target_link_libraries(sensor_actuator_test ernest SystemC XercesLib)

# task move test
add_executable(task_move_test task_move_test.cpp
                             swf_a.cpp
                             swf_b.cpp
                             swf_move.cpp)
target_link_libraries(task_move_test ernest SystemC XercesLib)

# execution specification interface test
add_executable(execution_specification_interface_test execution_specification_interface_test.cpp)
target_link_libraries(execution_specification_interface_test ernest SystemC XercesLib)

# flow port test
add_executable(flow_port_test flow_port_test.cpp
                              swf_a.cpp
                              swf_b.cpp)
target_link_libraries(flow_port_test ernest SystemC XercesLib)

# forwarding test
add_executable(forwarding_test forwarding_test.cpp
                               swf_a.cpp
                               swf_b.cpp
                               swf_c.cpp)
target_link_libraries(forwarding_test ernest SystemC XercesLib)

# alarm test
add_executable(alarm_test alarm_test.cpp
                          swf_test.cpp)                          
target_link_libraries(alarm_test ernest SystemC XercesLib)

# can bus test
add_executable(can_bus_test can_bus_test.cpp
							swf_a.cpp
							swf_b.cpp)
target_link_libraries(can_bus_test ernest SystemC XercesLib bt1lib)

# client server port test
add_executable(client_server_port_test client_server_port_test.cpp
								       swf_req.cpp
									   swf_prov.cpp)
target_link_libraries(client_server_port_test ernest SystemC XercesLib)

# scheduler test
add_executable(scheduler_test scheduler_test.cpp
                              swf_a.cpp
                              swf_b.cpp
                              swf_c.cpp)
target_link_libraries(scheduler_test ernest SystemC XercesLib)

# flow port multi test
add_executable(flow_port_multi_test flow_port_multi_test.cpp
                              swf_a.cpp
                              swf_b.cpp
                              swf_c.cpp)
target_link_libraries(flow_port_multi_test ernest SystemC XercesLib)

# installinstall(TARGETS execution_specification_interface_test RUNTIME DESTINATION tests)
install(TARGETS flow_port_test RUNTIME DESTINATION tests)
install(TARGETS forwarding_test RUNTIME DESTINATION tests)
