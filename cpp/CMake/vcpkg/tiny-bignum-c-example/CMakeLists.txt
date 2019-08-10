cmake_minimum_required(VERSION 3.9)

project(tiny-bignum-c-example C)

find_package(unofficial-tiny-bignum-c CONFIG REQUIRED)

file(DOWNLOAD
    "https://raw.githubusercontent.com/kokke/tiny-bignum-c/master/tests/factorial.c"
    "${CMAKE_CURRENT_BINARY_DIR}/factorial.c"
)

add_executable(factorial ${CMAKE_CURRENT_BINARY_DIR}/factorial.c)
target_link_libraries(
    factorial
    PRIVATE
        unofficial::tiny-bignum-c::tiny-bignum-c
)
