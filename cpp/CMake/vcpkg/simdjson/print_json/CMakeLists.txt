cmake_minimum_required(VERSION 3.10)

project(print_json CXX)

find_package(simdjson CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(DOWNLOAD
    "https://raw.githubusercontent.com/lemire/simdjson/master/jsonexamples/small/demo.json"
    "${CMAKE_CURRENT_LIST_DIR}/demo.json"
)

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
target_compile_features(print_json INTERFACE cxx_std_17)
target_link_libraries(print_json PRIVATE simdjson::simdjson)

# References:
# https://stackoverflow.com/questions/45688522/how-to-enable-c17-in-cmake
