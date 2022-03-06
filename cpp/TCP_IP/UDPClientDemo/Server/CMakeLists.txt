add_executable(Server Server.cpp)
target_link_libraries(Server PRIVATE UDPClient)

add_executable(Server_MSG_TRUNC Server.cpp)
target_link_libraries(Server_MSG_TRUNC PRIVATE UDPClient)
target_compile_definitions(Server_MSG_TRUNC PRIVATE USE_MSG_TRUNC)
