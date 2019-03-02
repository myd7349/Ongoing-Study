cmake_minimum_required(VERSION 3.8)

project(tell_me_the_answer)

find_package(unofficial-tiny-process-library CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(USE_STATIC_RTL "Use MSVC static runtime library." OFF)

if (USE_STATIC_RTL)
    if (MSVC)
        foreach(flag_var
            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
            if(${flag_var} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
            endif(${flag_var} MATCHES "/MD")
        endforeach(flag_var)
    endif (MSVC)
endif ()

add_executable(answer answer.c)
add_executable(tell_me tell_me.cpp)
target_compile_definitions(tell_me PRIVATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE)
target_link_libraries(tell_me PRIVATE unofficial::tiny-process-library::tiny-process-library)

# References:
# https://github.com/ampl/mp/pull/125/files
