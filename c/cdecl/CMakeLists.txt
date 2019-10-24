cmake_minimum_required(VERSION 3.8)
project(cdecl C)
add_executable(cdecl cdecl.c)
target_compile_definitions(cdecl PRIVATE $<$<C_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>)
