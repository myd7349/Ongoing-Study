cmake_minimum_required(VERSION 3.9)

project(protobuf-examples CXX)

find_package(protobuf CONFIG REQUIRED)
find_path(PLF_NANOTIMER_INCLUDE_DIR NAMES plf_nanotimer.h)

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

foreach (base_type int8 int16 int32)
    set(pack_data_exe "pack_data_${base_type}")

    add_executable(${pack_data_exe} ${CMAKE_CURRENT_LIST_DIR}/pack_data.cpp)

    # Code generation
    protobuf_generate(
        LANGUAGE cpp
        TARGET ${pack_data_exe}
        PROTOS ${CMAKE_CURRENT_LIST_DIR}/packed_data.proto
    )
    
    target_compile_definitions(
        ${pack_data_exe}
        PRIVATE
            BASE_TYPE=std::${base_type}_t
    )
    target_compile_options(
        ${pack_data_exe}
        PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:
                /wd4005
                /wd4251
            >
    )
    target_include_directories(${pack_data_exe} PRIVATE "${PLF_NANOTIMER_INCLUDE_DIR}")
    target_link_libraries(${pack_data_exe} PRIVATE protobuf::libprotobuf)
endforeach ()


# References:
# https://github.com/protocolbuffers/protobuf/blob/master/examples/CMakeLists.txt
# https://stackoverflow.com/questions/52533396/cmake-cant-find-protobuf-protobuf-generate-cpp
# https://stackoverflow.com/questions/16736819/protobuf-generate-cpp-during-creation-of-cmake-files
