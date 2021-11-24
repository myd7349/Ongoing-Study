cmake_minimum_required(VERSION 3.8)

project(list_network_interfaces C)
add_executable(list_network_interfaces list_network_interfaces.c)
target_include_directories(list_network_interfaces PRIVATE "${CMAKE_CURRENT_LIST_DIR}/..")
