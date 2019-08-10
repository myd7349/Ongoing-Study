cmake_minimum_required(VERSION 3.9)

project(tiny-aes-c-example C)

find_package(unofficial-tiny-aes-c CONFIG REQUIRED)

file(DOWNLOAD
    "https://raw.githubusercontent.com/kokke/tiny-AES-c/master/test.c"
    "${CMAKE_CURRENT_BINARY_DIR}/test.c"
)

add_executable(tiny-aes-c-example ${CMAKE_CURRENT_BINARY_DIR}/test.c)
target_link_libraries(
    tiny-aes-c-example
    PRIVATE
        unofficial::tiny-aes-c::tiny-aes-c
)
