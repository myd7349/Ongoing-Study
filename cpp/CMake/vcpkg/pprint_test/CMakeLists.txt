cmake_minimum_required(VERSION 3.9)

project(pprint_test CXX)

find_package(pprint CONFIG REQUIRED)

add_executable(pprint_test pprint_test.cpp)
if (MSVC)
    target_compile_options(pprint_test PRIVATE "/source-charset:utf-8")
endif (MSVC)
target_link_libraries(pprint_test PRIVATE pprint::pprint)
