cmake_minimum_required(VERSION 3.15)

project(subprocess_output LANGUAGES C CXX)

find_package(unofficial-tiny-process-library CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(USE_MSVC_STATIC_CRT "Use MSVC static runtime library." OFF)

if(USE_MSVC_STATIC_CRT)
    if(MSVC)
        foreach(flag_var
            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
            if(${flag_var} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
            endif(${flag_var} MATCHES "/MD")
        endforeach(flag_var)
    endif()
endif()

add_executable(subprocess_output-tpl subprocess_output-tpl.cpp)
add_executable(subprocess_output-popen subprocess_output-popen.c)
add_executable(subprocess_output-winapi subprocess_output-winapi.c)

if(MSVC)
    target_compile_definitions(
        subprocess_output-tpl
        PRIVATE
            _CRT_SECURE_NO_WARNINGS
            _CRT_NONSTDC_NO_DEPRECATE
    )
endif()

target_link_libraries(
    subprocess_output-tpl
    PRIVATE
        unofficial::tiny-process-library::tiny-process-library
)

target_link_libraries(
    subprocess_output-winapi
    PRIVATE
        strsafe.lib
)

add_executable(stdout_stderr_order stdout_stderr_order.cpp)
