cmake_minimum_required(VERSION 3.9)

project(metal_example CXX)

find_package(Metal CONFIG REQUIRED)

file(DOWNLOAD
    "https://raw.githubusercontent.com/brunocodutra/metal/master/example/src/tutorial.cpp"
    "${CMAKE_BINARY_DIR}/tutorial.cpp")
file(DOWNLOAD
    "https://raw.githubusercontent.com/brunocodutra/metal/master/example/include/example.hpp"
    "${CMAKE_BINARY_DIR}/example.hpp")

add_executable(metal_example "${CMAKE_BINARY_DIR}/tutorial.cpp")

target_link_libraries(metal_example PRIVATE Metal)
