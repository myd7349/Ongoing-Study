cmake_minimum_required(VERSION 3.9)

project(xeus_echo_example)

find_package(xeus CONFIG REQUIRED)

foreach(_f "echo_client.cpp" "echo_client.hpp" "main.cpp")
    file(DOWNLOAD
        "https://raw.githubusercontent.com/QuantStack/xeus/master/example/echo_client/${_f}"
        "${CMAKE_SOURCE_DIR}/echo_client/${_f}")
endforeach()

foreach(_f "connection.json" "echo_interpreter.cpp" "echo_interpreter.hpp" "kernel.json" "main.cpp")
    file(DOWNLOAD
        "https://raw.githubusercontent.com/QuantStack/xeus/master/example/echo_kernel/${_f}"
        "${CMAKE_SOURCE_DIR}/echo_kernel/${_f}")
endforeach()

message(STATUS "xeus_INCLUDE_DIR: ${xeus_INCLUDE_DIR}")
message(STATUS "xeus_LIBRARY: ${xeus_LIBRARY}")
message(STATUS "xeus_STATIC_LIBRARY: ${xeus_STATIC_LIBRARY}")

add_subdirectory(echo_client)
add_subdirectory(echo_kernel)
