cmake_minimum_required(VERSION 3.9)

project(kissfft_test C CXX)

option(KISSFFT_STATIC "Use kissfft static library." OFF)

#find_package(kissfft CONFIG REQUIRED COMPONENTS float)

if(KISSFFT_STATIC)
    find_package(kissfft CONFIG REQUIRED COMPONENTS STATIC float)
else()
    find_package(kissfft CONFIG REQUIRED COMPONENTS SHARED float)
endif()

add_executable(kissfft_test kissfft_test.cpp)
target_link_libraries(kissfft_test PRIVATE kissfft::kissfft)

if(TARGET kissfft::kissfft)
    message(STATUS "kissfft::kissfft is available.")
endif()

if(TARGET kissfft::kissfft-float)
    message(STATUS "kissfft::kissfft-float is available.")
endif()

if(TARGET kissfft::kissfft-double)
    message(STATUS "kissfft::kissfft-double is available.")
endif()
