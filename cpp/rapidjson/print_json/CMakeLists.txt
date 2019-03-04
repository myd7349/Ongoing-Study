cmake_minimum_required(VERSION 3.9)

project(print_json CXX)

find_package(rapidjson CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


option(USE_STATIC_CRT "Use static version of CRT." OFF)

if (USE_STATIC_CRT)
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

add_executable(print_json print_json.cpp)
target_include_directories(
    print_json
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/..>
    $<BUILD_INTERFACE:${RAPIDJSON_INCLUDE_DIRS}>
)

# References:
# https://stackoverflow.com/questions/45688522/how-to-enable-c17-in-cmake
