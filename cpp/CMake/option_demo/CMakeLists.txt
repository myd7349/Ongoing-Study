CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(CMakeOptionDemo CXX)

option(OLD_SCHOOL_STYLE "Use old-school style or not" OFF)
if(OLD_SCHOOL_STYLE)
    add_definitions(-DOLD_SCHOOL_STYLE)
endif()

add_executable(option_demo "option_demo.cpp")


# References:
# rapidjson:CMakeLists.txt
