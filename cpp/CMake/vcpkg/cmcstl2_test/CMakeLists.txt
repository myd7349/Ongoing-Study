cmake_minimum_required(VERSION 3.9)

project(cmcstl2-example CXX)

find_package(cmcstl2 CONFIG REQUIRED)

file(DOWNLOAD
    "https://raw.githubusercontent.com/CaseyCarter/cmcstl2/master/examples/simple.cpp"
    "${CMAKE_CURRENT_BINARY_DIR}/simple.cpp"
)

add_executable(simple ${CMAKE_CURRENT_BINARY_DIR}/simple.cpp)
target_link_libraries(simple PRIVATE stl2)
