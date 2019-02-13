cmake_minimum_required(VERSION 3.8)

project(ZeroMQHelloWorld LANGUAGES C)

find_package(ZeroMQ CONFIG REQUIRED)

add_executable(hwclient "Client/hwclient.c")
target_link_libraries(hwclient PRIVATE libzmq libzmq-static)

add_executable(hwserver "Server/hwserver.c")
target_link_libraries(hwserver PRIVATE libzmq libzmq-static)
