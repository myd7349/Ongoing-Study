cmake_minimum_required(VERSION 3.9)

project(override_malloc LANGUAGES C CXX)

if(MSVC)
    option(GPERFTOOLS_WIN32_OVERRIDE_ALLOCATORS "Overriding instead of patching" OFF)
    option(USE_STATIC_CRT "Use static version of CRT" ${GPERFTOOLS_WIN32_OVERRIDE_ALLOCATORS})

    if(USE_STATIC_CRT)
        if(MSVC)
            foreach(flag_var
                CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
                CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO
                CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
                CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
                if(${flag_var} MATCHES "/MD")
                    string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
                endif(${flag_var} MATCHES "/MD")
            endforeach(flag_var)
        endif(MSVC)
    endif()
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

find_package(gperftools REQUIRED)

add_executable(override_malloc override_malloc.c)
target_link_libraries(override_malloc PRIVATE gperftools::tcmalloc_minimal)

if(MSVC)
    if(GPERFTOOLS_WIN32_OVERRIDE_ALLOCATORS)
        set(CRT_DEBUG_LIBS
            libucrtd.lib
            libvcruntimed.lib
            libcmtd.lib
            LIBCPMTd.LIB
            libconcrtd.lib
            legacy_stdio_wide_specifiers.lib
            oldnames.lib
        )
        set(CRT_RELEASE_LIBS
            libucrt.lib
            libvcruntime.lib
            libcmt.lib
            LIBCPMT.LIB
            libconcrt.lib
            legacy_stdio_wide_specifiers.lib
            oldnames.lib
        )
        target_link_options(
            override_malloc
            PRIVATE
                #/INCLUDE:_malloc
                #/INCLUDE:__malloc_dbg
                /FORCE:MULTIPLE
                /NODEFAULTLIB
        )
        target_link_libraries(override_malloc PRIVATE ${CRT_RELEASE_LIBS})
    else()
        target_link_options(override_malloc PRIVATE /INCLUDE:__tcmalloc)
    endif()
endif()

# References:
# [override malloc in msvc](https://stackoverflow.com/questions/1316018/globally-override-malloc-in-visual-c)
# [Overridable CRT Release/Debug Memory functions (just like malloc)](https://developercommunity.visualstudio.com/idea/403088/overridable-crt-releasedebug-memory-functions-just.html)
# [Globally override malloc in visual c++](https://stackoverflow.com/questions/1316018/globally-override-malloc-in-visual-c)
