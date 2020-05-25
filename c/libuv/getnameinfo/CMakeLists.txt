cmake_minimum_required(VERSION 3.8)

project(tcp_echo_client C)

if(WIN32)
    if(MSVC)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS=1)
    endif()

    add_definitions(-DUSING_UNICODE=0)
endif()

add_executable(getnameinfo
    "getnameinfo.c"
    )

if(WIN32)
    target_include_directories(getnameinfo PRIVATE "$ENV{VCPKG_ROOT}/installed/x86-windows/include")

    target_link_libraries(getnameinfo PRIVATE "$ENV{VCPKG_ROOT}/installed/x86-windows/lib/libuv.lib")
    add_custom_command(TARGET getnameinfo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$ENV{VCPKG_ROOT}/installed/x86-windows/bin/libuv.dll"
            $<TARGET_FILE_DIR:getnameinfo>)
endif()
