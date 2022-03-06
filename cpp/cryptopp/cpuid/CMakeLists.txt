cmake_minimum_required(VERSION 3.8)

project(cpuid LANGUAGES CXX)

find_package(cryptopp CONFIG REQUIRED)

add_executable(cpuid cpuid.cpp)
target_link_libraries(cpuid PRIVATE cryptopp-static)

if(WIN32)
    add_executable(cpuid_win32 cpuid_win32.cpp)
endif()
