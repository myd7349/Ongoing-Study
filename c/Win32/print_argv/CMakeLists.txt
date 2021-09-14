cmake_minimum_required(VERSION 3.8)
project(print_argv C)

function(create_executable executable sources)
    add_executable(${executable} ${sources})
    target_compile_definitions(${executable} PRIVATE UNICODE _UNICODE)
    target_link_options(${executable} PRIVATE "/SUBSYSTEM:CONSOLE" "/ENTRY:wmainCRTStartup")
    target_link_libraries(${executable} PRIVATE Shell32)
endfunction()

create_executable(print_argv print_argv.c)

set(exec_root_dir "${CMAKE_CURRENT_LIST_DIR}/..")
set(exec_sources
    "${exec_root_dir}/Execute.c"
    "${exec_root_dir}/WindowsVersionHelpers.c"
)
add_library(exec STATIC ${exec_sources})
target_compile_definitions(exec PRIVATE UNICODE _UNICODE)
target_include_directories(exec PUBLIC "${exec_root_dir}")
target_link_libraries(exec PUBLIC Shell32)

create_executable(call_print_argv call_print_argv.c)
target_link_libraries(call_print_argv PRIVATE exec)


# References:
# [What's the equivalent of gcc's -mwindows option in cmake?](https://stackoverflow.com/questions/2752792/whats-the-equivalent-of-gccs-mwindows-option-in-cmake)
