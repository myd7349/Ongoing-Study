cmake_minimum_required(VERSION 3.12)

project(cppitertools_test LANGUAGES CXX)

find_package(Boost 1.68.0 REQUIRED)
find_path(
    CPPITERTOOLS_INCLUDE_DIR
    accumulate.hpp
    range.hpp
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message(STATUS "CPPITERTOOLS_INCLUDE_DIR: ${CPPITERTOOLS_INCLUDE_DIR}")

add_executable(cppitertools_test cppitertools_test.cpp)
target_include_directories(cppitertools_test PRIVATE ${CPPITERTOOLS_INCLUDE_DIR})
target_link_libraries(cppitertools_test PRIVATE Boost::boost)


# References:
# https://stackoverflow.com/questions/44960715/how-to-enable-stdc17-in-vs2017-with-cmake
