cmake_minimum_required(VERSION 3.8)

project(set_log_destination CXX)

find_package(glog CONFIG REQUIRED)

add_executable(set_log_destination "set_log_destination.cpp")

add_executable(set_log_destination_via_global_flag "set_log_destination.cpp")
target_compile_definitions(set_log_destination_via_global_flag PRIVATE SET_LOG_DIR_VIA_GLOBAL_FLAG)

if(MSVC AND MSVC_VERSION GREATER_EQUAL 1900)
    target_compile_options(set_log_destination PRIVATE /source-charset:utf-8)
    target_compile_options(set_log_destination_via_global_flag PRIVATE /source-charset:utf-8)
endif()

target_link_libraries(set_log_destination PRIVATE glog::glog)
target_link_libraries(set_log_destination_via_global_flag PRIVATE glog::glog)
