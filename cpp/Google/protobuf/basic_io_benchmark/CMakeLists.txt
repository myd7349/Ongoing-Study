cmake_minimum_required(VERSION 3.9)

project(basic_io_benchmark CXX)

find_package(benchmark CONFIG REQUIRED)
find_package(protobuf CONFIG REQUIRED)

option(RUN_BENCHMARK "Run benchmark" OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

# https://gitlab.kitware.com/cmake/community/wikis/FAQ#how-can-i-build-my-msvc-application-with-a-static-runtime
if(MSVC AND protobuf_MSVC_STATIC_RUNTIME)
    foreach(flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        if(${flag_var} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endif(${flag_var} MATCHES "/MD")
    endforeach()
endif()

add_executable(basic_io_benchmark "${CMAKE_CURRENT_LIST_DIR}/basic_io_benchmark.cpp")
protobuf_generate(
    LANGUAGE cpp
    TARGET basic_io_benchmark
    PROTOS "${CMAKE_CURRENT_LIST_DIR}/data_file.proto"
    PROTOC_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}"
)
target_compile_definitions(
    basic_io_benchmark
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:
            _CRT_SECURE_NO_WARNINGS
        >
)
target_compile_options(
    basic_io_benchmark
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:
            /wd4005
            /wd4251
        >
)
target_link_libraries(
    basic_io_benchmark
    PRIVATE
        benchmark::benchmark
        benchmark::benchmark_main
        protobuf::libprotobuf
)

if (RUN_BENCHMARK)
    add_custom_command(
         OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/benchmark_io_results.log"
         DEPENDS basic_io_benchmark
         COMMAND basic_io_benchmark
         VERBATIM
    )
    add_custom_target(
        benchmark_io_run ALL
        DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/benchmark_io_results.log"
        VERBATIM
    )
endif ()


# References:
# https://stackoverflow.com/questions/35847655/when-should-i-quote-variables
# libhydrogen
