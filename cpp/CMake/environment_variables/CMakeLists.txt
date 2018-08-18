cmake_minimum_required (VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake")
endif()

project(environment_variables)

enable_testing()

message(STATUS $ENV{VCPKG_DIR})
message(STATUS $ENV{Path})
message(STATUS ${CMAKE_TOOLCHAIN_FILE})

find_package(GTest REQUIRED)

if(GTEST_FOUND)
    message(STATUS ${GTEST_INCLUDE_DIRS})
    message(STATUS ${GTEST_LIBRARIES})
    message(STATUS ${GTEST_MAIN_LIBRARIES})
    message(STATUS ${GTEST_LIBRARY})
    message(STATUS ${GTEST_MAIN_LIBRARY})
else(GTEST_FOUND)
    message(FATAL_ERROR "gtest library not found")
endif(GTEST_FOUND)

# References:
# FindGTest.cmake

# `vcpkg.exe` is installed to `E:\vcpkg` on my PC.
# So I created a new environment variable:
# VCPKG_DIR: E:\vcpkg
