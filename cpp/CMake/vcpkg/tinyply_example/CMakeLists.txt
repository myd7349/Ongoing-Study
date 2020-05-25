cmake_minimum_required(VERSION 3.9)

project(tinyply_example CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(tinyply CONFIG REQUIRED)

option(USE_CMAKE_TARGET "Use CMake target." ON)
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

include(FetchContent)

FetchContent_Declare(
    tinyply
    GIT_REPOSITORY https://github.com/ddiakopoulos/tinyply.git
    GIT_TAG        ca7b279fb6c9af931ffdaed96a3b11ca3ccd79ea
)

FetchContent_GetProperties(tinyply)
if(NOT tinyply_POPULATED)
    FetchContent_Populate(tinyply)
endif()

if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/example.cpp")
    file(COPY "${tinyply_SOURCE_DIR}/source/example.cpp" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
endif()
if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/example-utils.hpp")
    file(COPY "${tinyply_SOURCE_DIR}/source/example-utils.hpp" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
endif()

add_executable(tinyply_example "${CMAKE_CURRENT_BINARY_DIR}/example.cpp")

if(USE_CMAKE_TARGET)
    target_link_libraries(tinyply_example PRIVATE tinyply)
else()
    find_library(tinyply_LIBRARY_DEBUG NAMES tinyplyd tinyply PATHS ${tinyply_LIBRARY_DIR}/../debug/lib NO_DEFAULT_PATH)
    find_library(tinyply_LIBRARY_RELEASE NAMES tinyply PATHS ${tinyply_LIBRARY_DIR}/lib NO_DEFAULT_PATH)
    include(SelectLibraryConfigurations)
    select_library_configurations(tinyply)

    message(STATUS "tinyply_INCLUDE_DIR: ${tinyply_INCLUDE_DIR}")
    message(STATUS "tinyply_LIBRARIES: ${tinyply_LIBRARIES}")

    target_include_directories(tinyply_example PRIVATE ${tinyply_INCLUDE_DIR})
    target_link_libraries(tinyply_example PRIVATE ${tinyply_LIBRARIES})
endif()
