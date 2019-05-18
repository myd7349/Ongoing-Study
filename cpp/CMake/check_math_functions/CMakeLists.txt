cmake_minimum_required(VERSION 3.8)

project(check_math_functions C)

include(CheckFunctionExists)
include(CheckLibraryExists)

check_function_exists(pow HAVE_POW)

if (HAVE_POW)
    message(STATUS "Found pow via check_function_exists(pow HAVE_POW): ${HAVE_POW}")
else ()
    message(STATUS "Couldn't found pow via check_function_exists(pow HAVE_POW): ${HAVE_POW}")

    check_library_exists(m pow "" HAVE_POW_IN_LIBM)

    if (HAVE_POW_IN_LIBM)
        message(STATUS "Found pow via check_library_exists(m pow \"\" HAVE_POW_IN_LIBM): ${HAVE_POW_IN_LIBM}")
    else ()
        message(STATUS "Couldn't Found pow via check_library_exists(m pow \"\" HAVE_POW_IN_LIBM): ${HAVE_POW_IN_LIBM}")
    endif ()
endif ()

if (NOT HAVE_POW AND NOT HAVE_POW_IN_LIBM)
    message(FATAL_ERROR "pow not found!")
endif ()

add_executable(pow_example pow_example.c)
if (HAVE_POW_IN_LIBM)
    target_link_libraries(pow_example PRIVATE m)
endif ()


# References:
# https://stackoverflow.com/questions/43412943/cmake-cant-detect-gcc-built-in-functions-such-as-sqrt-pow-exp-and-so-on
# https://stackoverflow.com/questions/32816646/can-cmake-detect-if-i-need-to-link-to-libm-when-using-pow-in-c
# https://github.com/edenhill/librdkafka/blob/v1.0.0/CMakeLists.txt#L38
# https://github.com/mesonbuild/meson/issues/5390#issuecomment-491640529
# > AFAIK the only platform still using -lm et al is Linux and even there
#   the GNU people are working on getting rid of them.
