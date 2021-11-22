cmake_minimum_required(VERSION 3.8)

project(ipc_test LANGUAGES C CXX)

find_package(czmq CONFIG REQUIRED)

function(create_executable target)
    add_executable(${target} ipc_test.cpp)

    if(TARGET czmq)
        target_link_libraries(${target} PRIVATE czmq)
    else()
        target_link_libraries(${target} PRIVATE czmq-static)
    endif()
endfunction()

create_executable(ipc_test)
target_compile_definitions(ipc_test PRIVATE TEST_IPC)

create_executable(inproc_test)
target_compile_definitions(inproc_test PRIVATE TEST_INPROC)

create_executable(tcp_test)

# References:
# https://github.com/Microsoft/vcpkg/blob/master/docs/users/integration.md
# https://blogs.msdn.microsoft.com/vcblog/2016/11/01/vcpkg-updates-static-linking-is-now-available/
# https://stackoverflow.com/questions/28350214/how-to-build-x86-and-or-x64-on-windows-from-command-line-with-cmake
# https://stackoverflow.com/questions/920500/what-is-the-purpose-of-cxa-pure-virtual
# https://stackoverflow.com/questions/10703876/gcc-undefined-cxa-pure-virtual