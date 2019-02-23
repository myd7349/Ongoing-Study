cmake_minimum_required(VERSION 3.9)

project(copy_file CXX)

find_package(stxxl CONFIG REQUIRED)
find_package(Threads REQUIRED)

file(DOWNLOAD
    "https://raw.githubusercontent.com/stxxl/stxxl/master/examples/containers/copy_file.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/copy_file.cpp")

if (USE_STATIC_RTL)
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

message("STXXL_INCLUDE_DIRS: ${STXXL_INCLUDE_DIRS}")

add_executable(copy_file "copy_file.cpp")

target_link_libraries(copy_file PRIVATE stxxl Threads::Threads)
