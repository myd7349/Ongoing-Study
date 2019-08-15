cmake_minimum_required(VERSION 3.9)

project(protobuf-examples CXX)

set(protobuf_MODULE_COMPATIBLE ON)
find_package(protobuf CONFIG REQUIRED)

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

set(root_url https://raw.githubusercontent.com/nemequ/portable-snippets/master/)

foreach (psnip_header
    builtin/builtin.h
    endian/endian.h
    exact-int/exact-int.h
    )
    file(DOWNLOAD
        ${root_url}${psnip_header}
        ${CMAKE_CURRENT_BINARY_DIR}/${psnip_header}
    )
endforeach ()

add_executable(main ${CMAKE_CURRENT_LIST_DIR}/main.cpp)

# Code generation
protobuf_generate(
    LANGUAGE cpp
    TARGET main
    PROTOS ${CMAKE_CURRENT_LIST_DIR}/new_data_format_meta.proto
    IMPORT_DIRS ${Protobuf_INCLUDE_DIRS}
)

target_compile_options(
    main
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:
            /wd4005
            /wd4251
        >
)

target_include_directories(main PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(main PRIVATE protobuf::libprotobuf)


# References:
# https://github.com/protocolbuffers/protobuf/blob/master/examples/CMakeLists.txt
# https://stackoverflow.com/questions/52533396/cmake-cant-find-protobuf-protobuf-generate-cpp
# https://stackoverflow.com/questions/16736819/protobuf-generate-cpp-during-creation-of-cmake-files
# https://stackoverflow.com/questions/56031098/protobuf-timestamp-not-found
