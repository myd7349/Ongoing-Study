cmake_minimum_required(VERSION 3.8)

project(base64 C CXX)

include(CTest)

option(BUILD_TOOLS "Build base64 tools" ON)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(base64 base64.c)

if (BUILD_TOOLS)
    add_subdirectory(tools)
endif ()

if (BUILD_TESTING)
    add_subdirectory(tests)
endif ()
