cmake_minimum_required(VERSION 3.9)

project(colored-cube CXX)

find_package(GLUT REQUIRED) # FreeGLUT

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(BINARY_FOLDER_SUFFIX x64)
else ()
    set(BINARY_FOLDER_SUFFIX x86)
endif ()

add_subdirectory(
    ${CMAKE_CURRENT_LIST_DIR}/../common
    ${CMAKE_CURRENT_LIST_DIR}/../common/build/${CMAKE_BUILD_TYPE}_${BINARY_FOLDER_SUFFIX}
)

add_executable(colored-cube colored-cube.cpp)

target_compile_definitions(
    colored-cube
    PRIVATE
        CUBE_ENABLE_DEPTH_TEST
        #CUBE_RANDOM_COLORS
        CUBE_RANDOM_COLORS_EACH_FRAME
)

target_link_libraries(
    colored-cube
    PRIVATE
        GLUT::GLUT
        liboglcommon
)

add_custom_command(
    TARGET colored-cube
    POST_BUILD
    COMMAND
        "${CMAKE_COMMAND}" -E copy_if_different
        "${CMAKE_CURRENT_LIST_DIR}/SimpleVertexShader.vertexshader"
        "${CMAKE_CURRENT_LIST_DIR}/SimpleFragmentShader.fragmentshader"
        $<TARGET_FILE_DIR:colored-cube>
    VERBATIM
)
