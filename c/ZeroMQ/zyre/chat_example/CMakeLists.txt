cmake_minimum_required(VERSION 3.8)

project(chat_example C CXX)

find_package(zyre CONFIG REQUIRED)

file(DOWNLOAD
    "https://raw.githubusercontent.com/zeromq/zyre/master/examples/chat/chat.c"
    "${CMAKE_CURRENT_BINARY_DIR}/chat.c"
)

add_executable(chat "${CMAKE_CURRENT_BINARY_DIR}/chat.c")

target_link_libraries(chat PRIVATE zyre zyre-static)
