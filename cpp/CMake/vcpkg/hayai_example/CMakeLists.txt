cmake_minimum_required(VERSION 3.9)

project(basic_io_benchmark CXX)

find_package(hayai CONFIG REQUIRED)
find_package(protobuf CONFIG REQUIRED)

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

add_executable(bench_assign ${CMAKE_CURRENT_LIST_DIR}/bench_assign.cpp)

protobuf_generate(
    LANGUAGE cpp
    TARGET bench_assign
    PROTOS ${CMAKE_CURRENT_LIST_DIR}/data_file.proto
)

if (MSVC)
    #add_definitions(/wd4005 /wd4251) # Works fine here! Protobuf's CMakeLists.txt uses this way.
    #add_compile_definitions(/wd4005 /wd4251) # Not works here!
    #add_compile_options(/wd4005 /wd4251) # Not Works here!
endif ()

target_include_directories(bench_assign PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
#target_compile_definitions(bench_assign PRIVATE /wd4005 /wd4251) # Not works here!
target_compile_options(
    bench_assign
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:
            /wd4005
            /wd4251
        >
)
target_link_libraries(
    bench_assign
    PRIVATE
        hayai_main
        protobuf::libprotobuf
)


# References:
# https://stackoverflow.com/questions/41205725/how-to-disable-specific-warning-inherited-from-parent-in-visual-studio
