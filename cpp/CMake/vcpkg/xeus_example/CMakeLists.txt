cmake_minimum_required(VERSION 3.9)

project(xeus_echo_example)

find_package(xeus CONFIG REQUIRED)
find_package(cryptopp CONFIG REQUIRED)

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

add_subdirectory(echo_client)
add_subdirectory(echo_kernel)
