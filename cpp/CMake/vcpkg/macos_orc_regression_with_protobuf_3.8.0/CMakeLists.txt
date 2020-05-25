cmake_minimum_required(VERSION 3.9)

project(protobuf-examples CXX)

find_package(protobuf CONFIG REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR TRUE)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# https://github.com/apache/orc/blob/45b368872542e1fa1b9be675ea21ced6c9f337d8/CMakeLists.txt#L77-L99
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    set(WARN_FLAGS "-Weverything -Wno-c++98-compat -Wno-missing-prototypes")
    set(WARN_FLAGS "${WARN_FLAGS} -Wno-c++98-compat-pedantic -Wno-padded")
    set(WARN_FLAGS "${WARN_FLAGS} -Wno-covered-switch-default")
    set(WARN_FLAGS "${WARN_FLAGS} -Wno-missing-noreturn -Wno-unknown-pragmas")
    set(WARN_FLAGS "${WARN_FLAGS} -Wno-gnu-zero-variadic-macro-arguments")
    set(WARN_FLAGS "${WARN_FLAGS} -Wconversion -Werror")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(WARN_FLAGS "-Wall -Wno-unknown-pragmas -Wconversion -Werror")
endif ()

foreach(flag_var
    CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
    CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    # https://github.com/apache/orc/blob/45b368872542e1fa1b9be675ea21ced6c9f337d8/c%2B%2B/src/CMakeLists.txt#L13
    set(${flag_var} "${${flag_var}} ${WARN_FLAGS}")
endforeach()

# http://www.cmake.org/Wiki/CMake_FAQ#How_can_I_build_my_MSVC_application_with_a_static_runtime.3F
if(MSVC AND protobuf_MSVC_STATIC_RUNTIME)
    foreach(flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        if(${flag_var} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endif(${flag_var} MATCHES "/MD")
    endforeach()
endif()

add_executable(person_cpp ${CMAKE_CURRENT_LIST_DIR}/person.cpp)

# Code generation
protobuf_generate(
    LANGUAGE cpp
    TARGET person_cpp
    PROTOS ${CMAKE_CURRENT_LIST_DIR}/person.proto
)

target_link_libraries(person_cpp PRIVATE protobuf::libprotobuf)
