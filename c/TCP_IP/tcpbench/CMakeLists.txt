cmake_minimum_required(VERSION 3.8)

project(tcpbench C)

add_definitions(-D_CRT_SECURE_NO_WARNINGS=1)

add_executable(tcpbench_client
    "start_client.c"
    "../tcpclient.c"
    "../get_in_addr.c"
    "../options.c"
    "../sendall.c"
    "../../getprogname.c"
    "../../high_timer.c"
    "../../ttoi.c"
    "../../../algorithm/string/stringview.c"
    "../../../algorithm/string/substr.c"
    )
add_executable(tcpbench_server
    "start_server.c"
    "../tcpsrv.c"
    "../get_in_addr.c"
    "../sendall.c"
    "../tcpopt.c"
    "../../high_timer.c"
    "../../ttoi.c"
    )

# Currently, find_package does work with `getopt-win32` when using vcpkg.
if(WIN32)
    target_include_directories(tcpbench_client PRIVATE "$ENV{VCPKG_ROOT}/installed/x86-windows/include")
    target_link_libraries(tcpbench_client PRIVATE "$ENV{VCPKG_ROOT}/installed/x86-windows/lib/getopt.lib")
    add_custom_command(TARGET tcpbench_client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$ENV{VCPKG_ROOT}/installed/x86-windows/bin/getopt.dll"
            $<TARGET_FILE_DIR:tcpbench_client>)
endif()
