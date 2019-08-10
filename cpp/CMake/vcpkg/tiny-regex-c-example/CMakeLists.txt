cmake_minimum_required(VERSION 3.9)

project(tiny-regex-c-example C)

find_package(unofficial-tiny-regex-c CONFIG REQUIRED)

file(DOWNLOAD
    "https://raw.githubusercontent.com/kokke/tiny-regex-c/master/tests/test1.c"
    "${CMAKE_CURRENT_BINARY_DIR}/test1.c"
)

add_executable(test1 ${CMAKE_CURRENT_BINARY_DIR}/test1.c)
target_link_libraries(
    test1
    PRIVATE
        unofficial::tiny-regex-c::tiny-regex-c
)
