cmake_minimum_required(VERSION 3.9)

project(matrices CXX)

find_package(GLEW REQUIRED) # GLEW
find_package(glfw3 CONFIG REQUIRED) # GLFW
find_package(glm CONFIG REQUIRED)
find_package(GLUT REQUIRED) # FreeGLUT

if(CMAKE_CL_64)
    set(BINARY_FOLDER_SUFFIX x64)
else()
    set(BINARY_FOLDER_SUFFIX x86)
endif()

add_subdirectory(
    ${CMAKE_CURRENT_LIST_DIR}/../../common
    ${CMAKE_CURRENT_LIST_DIR}/../../common/build/${CMAKE_BUILD_TYPE}_${BINARY_FOLDER_SUFFIX}
)

add_executable(matrices matrices.cpp)

target_link_libraries(
    matrices
    PRIVATE
        GLEW::GLEW
        glfw
        glm
        GLUT::GLUT
        liboglcommon
)

add_custom_command(
    TARGET matrices
    POST_BUILD
    COMMAND
        "${CMAKE_COMMAND}" -E copy_if_different
        "${CMAKE_CURRENT_LIST_DIR}/SimpleVertexShader.vertexshader"
        "${CMAKE_CURRENT_LIST_DIR}/SimpleFragmentShader.fragmentshader"
        $<TARGET_FILE_DIR:matrices>
    VERBATIM
)
