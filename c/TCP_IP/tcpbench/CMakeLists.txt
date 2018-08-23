cmake_minimum_required(VERSION 3.8)

project(tchbench C)

add_executable(tchbench_client
    "start_client.c"
    "../tcpclient.c"
    "../get_in_addr.c"
    "../sendall.c"
    "../../high_timer.c"
    "../../ttoi.c"
    )
add_executable(tchbench_server
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
    target_include_directories(tchbench_client PRIVATE "$ENV{VCPKG_DIR}/installed/x86-windows/include")
    target_link_libraries(tchbench_client PRIVATE "$ENV{VCPKG_DIR}/installed/x86-windows/lib/getopt.lib")
    add_custom_command(TARGET tchbench_client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$ENV{VCPKG_DIR}/installed/x86-windows/bin/getopt.dll"
            $<TARGET_FILE_DIR:tchbench_client>)
endif()
