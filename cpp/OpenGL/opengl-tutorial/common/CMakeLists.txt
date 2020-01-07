cmake_minimum_required(VERSION 3.9)

project(liboglcommon C CXX)

find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_library(
    liboglcommon
    controls.cpp
    nv_dds.cpp
    shader.cpp
    texture.cpp
)

target_include_directories(
    liboglcommon
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)

target_compile_definitions(
    liboglcommon
    PRIVATE
        $<$<C_COMPILER_ID:MSVC>:
            _CRT_SECURE_NO_WARNINGS
        >
        NV_DDS_NO_GL_SUPPORT
)

target_link_libraries(
    liboglcommon
    PUBLIC
        GLEW::GLEW
        glfw
        glm
)
