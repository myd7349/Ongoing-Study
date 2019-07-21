cmake_minimum_required(VERSION 3.8)

project(foonathan-memory-example CXX)

find_package(foonathan_memory CONFIG REQUIRED)

option(USE_MSVC_STATIC_RUNTIME "Use static version of CRT." OFF)

if (USE_MSVC_STATIC_RUNTIME)
    if (MSVC)
        foreach(flag_var
            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
            if(${flag_var} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
            endif(${flag_var} MATCHES "/MD")
        endforeach(flag_var)
    endif (MSVC)
endif (USE_MSVC_STATIC_RUNTIME)

file(DOWNLOAD
    "https://raw.githubusercontent.com/foonathan/memory/master/example/using_allocators.cpp"
    "${CMAKE_CURRENT_BINARY_DIR}/using_allocators.cpp"
)

add_executable(using_allocators ${CMAKE_CURRENT_BINARY_DIR}/using_allocators.cpp)
target_link_libraries(using_allocators PRIVATE foonathan_memory)
