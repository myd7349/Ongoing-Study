cmake_minimum_required(VERSION 3.9)

project(onig_count C)

find_package(oniguruma CONFIG REQUIRED)

file(DOWNLOAD
    "https://raw.githubusercontent.com/kkos/oniguruma/master/sample/count.c"
    "${CMAKE_CURRENT_LIST_DIR}/count.c")

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

add_executable(onig_count "count.c")

target_link_libraries(onig_count PRIVATE oniguruma::onig)
