add_executable(Server Server.cpp)
target_link_libraries(Server PRIVATE Socket)

add_executable(Server_MSG_TRUNC Server.cpp)
target_link_libraries(Server_MSG_TRUNC PRIVATE Socket)
target_compile_definitions(Server_MSG_TRUNC PRIVATE USE_MSG_TRUNC)
