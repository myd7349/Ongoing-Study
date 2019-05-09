cmake_minimum_required(VERSION 3.8)
project(tcp_daytime C)

set(common_sources)

if (MINGW)
    file(DOWNLOAD
        "https://raw.githubusercontent.com/coderforlife/mingw-unicode-main/master/mingw-unicode.c"
        "${CMAKE_CURRENT_BINARY_DIR}/mingw-unicode.c"
    )

    include_directories("${CMAKE_CURRENT_BINARY_DIR}")
    list(APPEND common_sources
        ${CMAKE_CURRENT_LIST_DIR}/../get_in_addr.c
        ${CMAKE_CURRENT_LIST_DIR}/../inet_pton.c
    )
endif ()

add_executable(tcp_daytime_client_ipv4 tcp_daytime_client_ipv4.c ${common_sources})
if (WIN32)
    target_link_libraries(tcp_daytime_client_ipv4 PRIVATE ws2_32)
endif ()

add_executable(tcp_daytime_client_ipv6 tcp_daytime_client_ipv6.c ${common_sources})
if (WIN32)
    target_link_libraries(tcp_daytime_client_ipv6 PRIVATE ws2_32)
endif ()

add_executable(
    tcp_daytime_server_ipv4
	tcp_daytime_server_ipv4
	${CMAKE_CURRENT_LIST_DIR}/../sendall.c
    ${common_sources}
)
if (WIN32)
    target_link_libraries(tcp_daytime_server_ipv4 PRIVATE ws2_32)
endif ()

# References:
# https://stackoverflow.com/questions/15370033/how-to-use-inet-pton-with-the-mingw-compiler
# https://stackoverflow.com/questions/3571250/wwinmain-unicode-and-mingw
