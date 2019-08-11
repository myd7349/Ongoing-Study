cmake_minimum_required(VERSION 3.9)

project(tiny-regex-c-example C)

find_package(hydrogen CONFIG REQUIRED)

file(DOWNLOAD
    "https://raw.githubusercontent.com/jedisct1/libhydrogen/master/tests/tests.c"
    "${CMAKE_CURRENT_BINARY_DIR}/tests.c"
)

add_executable(tests ${CMAKE_CURRENT_BINARY_DIR}/tests.c)
target_link_libraries(tests PRIVATE hydrogen::hydrogen)
