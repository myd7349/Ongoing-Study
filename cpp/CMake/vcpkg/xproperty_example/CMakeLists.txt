cmake_minimum_required(VERSION 3.8)

project(xproperty_example CXX)

find_package(xproperty CONFIG REQUIRED)

if (xproperty_FOUND)
    message(STATUS "xproperty_INCLUDE_DIR: ${xproperty_INCLUDE_DIR}")
endif (xproperty_FOUND)

add_executable(xproperty_example xproperty_example.cpp)
target_link_libraries(xproperty_example PRIVATE xproperty)
#target_include_directories(xproperty_example PRIVATE ${xproperty_INCLUDE_DIR})
