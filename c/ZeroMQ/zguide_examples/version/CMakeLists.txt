cmake_minimum_required(VERSION 3.8)

project(zversion LANGUAGES C)

find_package(ZeroMQ CONFIG REQUIRED)

find_path (
    LIBZMQ_INCLUDE_DIRS
    NAMES zmq.h
)

message(STATUS "LIBZMQ_INCLUDE_DIRS: ${LIBZMQ_INCLUDE_DIRS}")

file(STRINGS "${LIBZMQ_INCLUDE_DIRS}/zmq.h" zmq_version_defines
     REGEX "#define ZMQ_VERSION_(MAJOR|MINOR|PATCH)")
foreach(ver ${zmq_version_defines})
    if(ver MATCHES "#define ZMQ_VERSION_(MAJOR|MINOR|PATCH) +([^ ]+)$")
        set(ZMQ_VERSION_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()

set(ZMQ_VERSION ${ZMQ_VERSION_MAJOR}.${ZMQ_VERSION_MINOR}.${ZMQ_VERSION_PATCH})
message(STATUS "0MQ version: v${ZMQ_VERSION}")

add_executable(version "version.c")
target_link_libraries(version PRIVATE libzmq libzmq-static)

# References:
# https://github.com/QuantStack/xeus/blob/master/CMakeLists.txt
