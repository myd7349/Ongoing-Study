cmake_minimum_required(VERSION 3.8)

project(check_compiler_flags C)

include(CheckCCompilerFlag)

function (compile_with_flag_if_possible target flag)
    set(_quiet_old_value ${CMAKE_REQUIRED_QUIET})
    set(CMAKE_REQUIRED_QUIET ON)

    check_c_compiler_flag(${flag} IS_KNOWN_FLAG)
    if (IS_KNOWN_FLAG)
        message(STATUS "Check if the compiler supports this flag: ${flag} - Success")
        target_compile_options(${target} PRIVATE ${flag})
    else ()
        message(STATUS "Check if the compiler supports this flag: ${flag} - Failed")
    endif ()
    unset(IS_KNOWN_FLAG CACHE)

    set(CMAKE_REQUIRED_QUIET ${_quiet_old_value})
endfunction ()

add_executable(hello hello.c)

compile_with_flag_if_possible(hello -Wall)
compile_with_flag_if_possible(hello -Wextra)
compile_with_flag_if_possible(hello -Wbad-function-cast)
compile_with_flag_if_possible(hello -Wcast-qual)
compile_with_flag_if_possible(hello -Wdiv-by-zero)
compile_with_flag_if_possible(hello -Wduplicated-branches)
compile_with_flag_if_possible(hello -Wduplicated-cond)
compile_with_flag_if_possible(hello -Wfloat-equal)
compile_with_flag_if_possible(hello -Wformat=2)
compile_with_flag_if_possible(hello -Wlogical-op)
compile_with_flag_if_possible(hello -Wmaybe-uninitialized)
compile_with_flag_if_possible(hello -Wmisleading-indentation)
compile_with_flag_if_possible(hello -Wmissing-declarations)
compile_with_flag_if_possible(hello -Wmissing-prototypes)
compile_with_flag_if_possible(hello -Wnested-externs)
compile_with_flag_if_possible(hello -Wno-type-limits)
compile_with_flag_if_possible(hello -Wno-unknown-pragmas)
compile_with_flag_if_possible(hello -Wnormalized=id)
compile_with_flag_if_possible(hello -Wnull-dereference)
compile_with_flag_if_possible(hello -Wold-style-declaration)
compile_with_flag_if_possible(hello -Wpointer-arith)
compile_with_flag_if_possible(hello -Wredundant-decls)
compile_with_flag_if_possible(hello -Wrestrict)
compile_with_flag_if_possible(hello -Wshorten-64-to-32)
compile_with_flag_if_possible(hello -Wsometimes-uninitialized)
compile_with_flag_if_possible(hello -Wstrict-prototypes)
compile_with_flag_if_possible(hello -Wswitch-enum)
compile_with_flag_if_possible(hello -Wvariable-decl)
compile_with_flag_if_possible(hello -Wwrite-strings)

#AX_CHECK_LINK_FLAG([-Wl,-z,relro
#AX_CHECK_LINK_FLAG([-Wl,-z,now
#AX_CHECK_LINK_FLAG([-Wl,-z,noexecstack


# References:
# https://github.com/raysan5/raylib/blob/master/cmake/AddIfFlagCompiles.cmake
# https://github.com/jedisct1/libsodium/blob/master/configure.ac
