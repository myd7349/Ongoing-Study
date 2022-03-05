cmake_minimum_required(VERSION 3.8)

project(HelloWorld LANGUAGES C CXX)

find_package(cppzmq CONFIG REQUIRED)

function(download_source source)
    if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/${source}")
        file(DOWNLOAD
            "https://raw.githubusercontent.com/booksbyus/zguide/master/examples/C%2B%2B/${source}"
            "${CMAKE_CURRENT_BINARY_DIR}/${source}")
    endif()
endfunction()

download_source(hwserver.cpp)
add_executable(hwserver "${CMAKE_CURRENT_BINARY_DIR}/hwserver.cpp")
target_link_libraries(hwserver PRIVATE cppzmq cppzmq-static)

download_source(hwclient.cpp)
add_executable(hwclient "${CMAKE_CURRENT_BINARY_DIR}/hwclient.cpp")
target_link_libraries(hwclient PRIVATE cppzmq cppzmq-static)
