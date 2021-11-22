cmake_minimum_required(VERSION 3.8)

project(ipc_test LANGUAGES C CXX)

find_package(ZeroMQ CONFIG REQUIRED)

function(create_executable target)
    add_executable(${target} ipc_test.c)

    target_include_directories(${target} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/..")

    target_compile_definitions(
        ${target}
        PRIVATE
            $<$<C_COMPILER_ID:MSVC>:
                _CRT_SECURE_NO_WARNINGS
                _CRT_NONSTDC_NO_DEPRECATE
            >
    )

    if(TARGET libzmq)
        target_link_libraries(${target} PRIVATE libzmq)
    else()
        target_link_libraries(${target} PRIVATE libzmq-static)
    endif()
endfunction()

create_executable(ipc_test)
target_compile_definitions(ipc_test PRIVATE TEST_IPC)

create_executable(tcp_test)
