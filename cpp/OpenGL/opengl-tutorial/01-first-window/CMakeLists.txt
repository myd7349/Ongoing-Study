cmake_minimum_required(VERSION 3.9)

project(first-window CXX)

find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED) # GLFW
find_package(GLUT REQUIRED) # FreeGLUT

add_executable(first-window first-window.cpp)

target_link_libraries(first-window PRIVATE GLEW::GLEW glfw GLUT::GLUT)
