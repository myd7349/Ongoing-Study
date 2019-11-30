cmake_minimum_required(VERSION 3.9)

project(glm-examples CXX)

find_package(glm CONFIG REQUIRED)

add_executable(glm-examples glm-examples.cpp)

target_link_libraries(glm-examples PRIVATE glm)
