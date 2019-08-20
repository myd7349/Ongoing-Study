cmake_minimum_required(VERSION 3.9)

project(byteswap_benchmark CXX)

find_package(benchmark CONFIG REQUIRED)

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

add_executable(byteswap_benchmark "${CMAKE_CURRENT_LIST_DIR}/byteswap_benchmark.cpp")

target_compile_definitions(
    byteswap_benchmark
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:
            _CRT_SECURE_NO_WARNINGS
        >
)
target_compile_options(
    byteswap_benchmark
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:
            /wd4005
            /wd4251
        >
)
target_link_libraries(
    byteswap_benchmark
    PRIVATE
        benchmark::benchmark
        benchmark::benchmark_main
)

if (RUN_BENCHMARK)
    add_custom_command(
         OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/byteswap_benchmark.log"
         DEPENDS byteswap_benchmark
         COMMAND byteswap_benchmark
         VERBATIM
    )
    add_custom_target(
        byteswap_benchmark_run ALL
        DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/byteswap_benchmark.log"
        VERBATIM
    )
endif ()


# References:
# https://stackoverflow.com/questions/35847655/when-should-i-quote-variables
# libhydrogen
