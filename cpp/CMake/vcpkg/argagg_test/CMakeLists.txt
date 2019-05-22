cmake_minimum_required(VERSION 3.9)

project(argagg_test)

foreach (_file doctest.h test.cpp)
    file(DOWNLOAD
        https://raw.githubusercontent.com/vietjtnguyen/argagg/master/test/${_file}
        ${CMAKE_CURRENT_BINARY_DIR}/${_file}
    )
endforeach ()

find_path(ARGAGG_INCLUDE_DIR argagg/argagg.hpp)

add_executable(argagg_test ${CMAKE_CURRENT_BINARY_DIR}/test.cpp)
target_include_directories(argagg_test PRIVATE ${ARGAGG_INCLUDE_DIR})
