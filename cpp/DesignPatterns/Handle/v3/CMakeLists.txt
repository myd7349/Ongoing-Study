cmake_minimum_required(VERSION 3.8)

project(handle_test CXX)

option(ENABLE_SANITIZERS "Enables AddressSanitizer." OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(handle_test "handle_test.cpp")

if (CMAKE_C_COMPILER_ID STREQUAL "GNUC")
    target_compile_options(
        handle_test
        PRIVATE
            -fsanitize=address
    )
endif ()

# References:
# cJson/CMakeLists.txt

