cmake_minimum_required(VERSION 3.8)
project(tcp_daytime C)
add_executable(tcp_daytime_client_ipv4 tcp_daytime_client_ipv4.c)
add_executable(tcp_daytime_client_ipv6 tcp_daytime_client_ipv6.c)
add_executable(
    tcp_daytime_server_ipv4
	tcp_daytime_server_ipv4
	${CMAKE_CURRENT_LIST_DIR}/../sendall.c
)
