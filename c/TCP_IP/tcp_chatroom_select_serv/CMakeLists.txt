cmake_minimum_required(VERSION 3.8)

project(tcpchatroomserv C)

set(SRCS
    "start_select_server.c"
    "../tcpsrv.c"
    "../get_in_addr.c"
    "../sendall.c"
    "../tcpopt.c"
    "../../ttoi.c"
    )

add_executable(tcpchatroomserv ${SRCS})
