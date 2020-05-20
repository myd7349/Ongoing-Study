cmake_minimum_required(VERSION 3.10)

project(print_json CXX)

find_package(simdjson CONFIG REQUIRED)
find_path(HAVE_TOP_LEVEL_SIMDJSON_HEADER NAMES simdjson.h)
find_package(Threads REQUIRED)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
include(EnableSanitizers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(MSVC_USE_STATIC_CRT "Use static version of CRT." OFF)

if(MSVC_USE_STATIC_CRT)
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

if(HAVE_TOP_LEVEL_SIMDJSON_HEADER)
    add_executable(print_json print_json.cpp)
else()
    message(WARNING "You are using deprecated simdjson APIs.")
    add_executable(print_json print_json_deprecated.cpp)
endif()

target_compile_features(print_json INTERFACE cxx_std_17)
target_link_libraries(print_json PRIVATE simdjson::simdjson)

# References:
# https://stackoverflow.com/questions/45688522/how-to-enable-c17-in-cmake
# https://github.com/googleapis/google-cloud-cpp/blob/v0.9.x/cmake/EnableSanitizers.cmake
