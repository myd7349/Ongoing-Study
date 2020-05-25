cmake_minimum_required(VERSION 3.9)

project(keyboard-and-mouse CXX)

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

function(create_target target_name)
    add_executable(${target_name} keyboard-and-mouse.cpp)

    target_link_libraries(
        ${target_name}
        PRIVATE
            GLUT::GLUT
            liboglcommon
    )

    add_custom_command(
        TARGET ${target_name}
        POST_BUILD
        COMMAND
            "${CMAKE_COMMAND}" -E copy_if_different
            "${CMAKE_CURRENT_LIST_DIR}/../05-textured-cube/TextureFragmentShader.fragmentshader"
            "${CMAKE_CURRENT_LIST_DIR}/../05-textured-cube/TransformVertexShader.vertexshader"
            "${CMAKE_CURRENT_LIST_DIR}/../05-textured-cube/uvtemplate.bmp"
            "${CMAKE_CURRENT_LIST_DIR}/../05-textured-cube/uvtemplate.dds"
            $<TARGET_FILE_DIR:${target_name}>
        VERBATIM
    )
endfunction()

create_target(keyboard-and-mouse-bmp)
target_compile_definitions(keyboard-and-mouse-bmp PRIVATE BMP_TEXTURE)

create_target(keyboard-and-mouse-dds)
