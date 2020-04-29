cmake_minimum_required(VERSION 3.8)

project(win32_getopt VERSION 1.0.2 LANGUAGES C)

find_path(GETOPT_INCLUDE_DIR NAMES getopt.h)
find_library(GETOPT_LIBRARY NAMES getopt)

include(CheckFunctionExists)
include(CheckSymbolExists)

if(GETOPT_INCLUDE_DIR)
    list(APPEND CMAKE_REQUIRED_INCLUDES "${GETOPT_INCLUDE_DIR}")
    check_symbol_exists(getopt_long "${GETOPT_INCLUDE_DIR}/getopt.h" HAVE_GETOPT_LONG_2)
    message(STATUS "HAVE_GETOPT_LONG_2: ${HAVE_GETOPT_LONG_2}")
endif()

check_function_exists(getopt_long HAVE_GETOPT_LONG_FUNC)
check_symbol_exists(getopt_long "getopt.h" HAVE_GETOPT_LONG_SYM)

message(STATUS "GETOPT_INCLUDE_DIR: ${GETOPT_INCLUDE_DIR}")
message(STATUS "GETOPT_LIBRARY: ${GETOPT_LIBRARY}")
message(STATUS "HAVE_GETOPT_LONG_FUNC: ${HAVE_GETOPT_LONG_FUNC}")
message(STATUS "HAVE_GETOPT_LONG_SYM: ${HAVE_GETOPT_LONG_SYM}")

add_executable(getopt_long_test "${CMAKE_CURRENT_LIST_DIR}/../getopt_long_test/getopt_long_test.c")

if(GETOPT_INCLUDE_DIR AND GETOPT_LIBRARY)
    target_include_directories(getopt_long_test PRIVATE ${GETOPT_INCLUDE_DIR})
    target_link_libraries(getopt_long_test PRIVATE ${GETOPT_LIBRARY})
endif()

# References:
# https://gitlab.freedesktop.org/uchardet/uchardet/-/merge_requests/3
# > Now I have done a bit of search and getopt seems indeed a POSIX lib which is not available by default in Windows, so maybe with some specific build environment, it is not available (it is at least available when building with Mingw-w64, as in our CI). Maybe a test can be useful but it must consider this fact in order not to break other build environments. You could for instance link with this lib if you find it, but not make not-finding it a build break at first. When not finding the lib, make a build test for the getopt.h header and getopt_long() function.
# > I suggest you remove this getopt part from this MR, then I'll just merge it. After this, you can open a separate MR for the getopt code with the right tests, if you wish. :-)
# https://github.com/kimgr/getopt_port
