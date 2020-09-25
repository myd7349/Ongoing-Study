cmake_minimum_required(VERSION 3.8)

project(strutils_test CXX)
add_executable(strutils_test strutils_test.cpp)
if(MSVC AND NOT (MSVC_VERSION LESS 1900))
    target_compile_options(strutils_test PRIVATE "/source-charset:utf-8")
endif()
