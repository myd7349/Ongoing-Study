cmake_minimum_required(VERSION 3.9)

project(find_libfoo_test C)

message(STATUS "CMAKE_LIBRARY_ARCHITECTURE: ${CMAKE_LIBRARY_ARCHITECTURE}")
message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
message(STATUS "CMAKE_FRAMEWORK_PATH: ${CMAKE_FRAMEWORK_PATH}")

set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR}/build/libfoo)

find_library(
    foo_LIBRARY
    NAMES libfoo
)
message(STATUS "foo_LIBRARY: ${foo_LIBRARY}")

unset(foo_LIBRARY CACHE)
message(STATUS "foo_LIBRARY: ${foo_LIBRARY}")
find_library(
    foo_LIBRARY
    NAMES foo
)
message(STATUS "foo_LIBRARY: ${foo_LIBRARY}")

unset(foo_LIBRARY CACHE)
find_library(
    foo_LIBRARY
    NAMES libfoo
    HINTS ${CMAKE_CURRENT_LIST_DIR}/build/libfoo
    NO_DEFAULT_PATH
)
message(STATUS "foo_LIBRARY: ${foo_LIBRARY}")

unset(foo_LIBRARY CACHE)
find_library(
    foo_LIBRARY
    NAMES libfoo
    HINTS ${CMAKE_CURRENT_LIST_DIR}/build/libfoo/lib
    NO_DEFAULT_PATH
)
message(STATUS "foo_LIBRARY: ${foo_LIBRARY}")

unset(foo_LIBRARY CACHE)
find_library(
    foo_LIBRARY
    NAMES foo
    HINTS ${CMAKE_CURRENT_LIST_DIR}/build/libfoo/lib
    NO_DEFAULT_PATH
)
message(STATUS "foo_LIBRARY: ${foo_LIBRARY}")


# References:
# https://stackoverflow.com/questions/16308847/how-to-clear-delete-a-cache-variable
