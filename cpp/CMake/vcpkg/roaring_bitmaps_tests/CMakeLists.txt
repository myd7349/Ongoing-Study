cmake_minimum_required(VERSION 3.8)

project(roaring-tests CXX)

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

add_subdirectory(src)
