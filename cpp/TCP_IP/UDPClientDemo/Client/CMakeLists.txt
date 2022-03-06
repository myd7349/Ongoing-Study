add_executable(Client Client.cpp)
target_link_libraries(Client PRIVATE UDPClient)

add_executable(Client_MSG_TRUNC Client.cpp)
target_link_libraries(Client_MSG_TRUNC PRIVATE UDPClient)
target_compile_definitions(Client_MSG_TRUNC PRIVATE USE_MSG_TRUNC)
