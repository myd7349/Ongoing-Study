add_executable(Server Server.cpp)
target_link_libraries(Server PRIVATE UDPClient)
