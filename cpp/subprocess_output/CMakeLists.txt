cmake_minimum_required(VERSION 3.15)

project(subprocess_output LANGUAGES C CXX)

find_package(Boost 1.68.0 COMPONENTS filesystem REQUIRED)
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

add_library(
    subprocess
    STATIC
    "${CMAKE_CURRENT_LIST_DIR}/../Win32/SDK/Error.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/../Win32/SDK/Subprocess.cpp"
)

target_include_directories(
    subprocess
    PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/../Win32/SDK/"
)

add_executable(subprocess_output-winapi-wrapper subprocess_output-winapi-wrapper.cpp)
target_link_libraries(subprocess_output-winapi-wrapper PRIVATE subprocess)

add_executable(subprocess_output-boost subprocess_output-boost.cpp)
target_include_directories(subprocess_output-boost PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(subprocess_output-boost PRIVATE Boost::filesystem)

# References:
# [cannot find boost_process cmake find_package](https://stackoverflow.com/questions/45931450/cannot-find-boost-process-cmake-find-package)
# https://cmake.org/cmake/help/v3.12/module/FindBoost.html
