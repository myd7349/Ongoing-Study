cmake_minimum_required(VERSION 3.8)

project(tcp_echo_client C)

if(WIN32)
    if(MSVC)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS=1)
    endif()

    add_definitions(-DUSING_UNICODE=0)
endif()

add_executable(tcp_echo_client
    "tcp_echo_client.c"
    )

if(WIN32)
    target_include_directories(tcp_echo_client PRIVATE "$ENV{VCPKG_ROOT}/installed/x86-windows/include")

    target_link_libraries(tcp_echo_client PRIVATE "$ENV{VCPKG_ROOT}/installed/x86-windows/lib/getopt.lib")
    add_custom_command(TARGET tcp_echo_client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$ENV{VCPKG_ROOT}/installed/x86-windows/bin/getopt.dll"
            $<TARGET_FILE_DIR:tcp_echo_client>)

    target_link_libraries(tcp_echo_client PRIVATE "$ENV{VCPKG_ROOT}/installed/x86-windows/lib/libuv.lib")
    add_custom_command(TARGET tcp_echo_client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$ENV{VCPKG_ROOT}/installed/x86-windows/bin/libuv.dll"
            $<TARGET_FILE_DIR:tcp_echo_client>)
endif()
