cmake_minimum_required(VERSION 3.8)

project(libm_test C)

include(CheckSymbolExists)

add_executable(libm_test libm_test.c)

if(NOT POW_FUNCTION_EXISTS AND NOT NEED_LINKING_AGAINST_LIBM)
    check_symbol_exists(pow "math.h" POW_FUNCTION_EXISTS)
    if(NOT POW_FUNCTION_EXISTS)
        unset(POW_FUNCTION_EXISTS CACHE)
        list(APPEND CMAKE_REQUIRED_LIBRARIES m)
        check_symbol_exists(pow "math.h" POW_FUNCTION_EXISTS)
        if(POW_FUNCTION_EXISTS)
            set(NEED_LINKING_AGAINST_LIBM True CACHE BOOL "" FORCE)
        else()
            message(FATAL_ERROR "Failed making the pow() function available")
        endif()
    endif()
endif()

if(NEED_LINKING_AGAINST_LIBM)
    target_link_libraries(libm_test PRIVATE m)
endif()

# References:
# [Can CMake detect if I need to link to libm when using pow in C?](https://stackoverflow.com/questions/32816646/can-cmake-detect-if-i-need-to-link-to-libm-when-using-pow-in-c)
