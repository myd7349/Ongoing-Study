cmake_minimum_required(VERSION 3.8)

project(foo CXX)

include(CTest)

add_subdirectory(src)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif ()
