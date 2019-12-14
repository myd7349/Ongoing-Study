cmake_minimum_required(VERSION 3.9)

project(triangles CXX)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(BINARY_FOLDER_SUFFIX x64)
else()
    set(BINARY_FOLDER_SUFFIX x86)
endif()

add_subdirectory(
    ${CMAKE_CURRENT_LIST_DIR}/../lib
    ${CMAKE_CURRENT_LIST_DIR}/../lib/build/${CMAKE_BUILD_TYPE}_${BINARY_FOLDER_SUFFIX}
)

add_executable(triangles triangles.cpp)

target_link_libraries(triangles PRIVATE libredbook)

if (WIN32)
    set_target_properties(triangles PROPERTIES WIN32_EXECUTABLE ON)
endif ()

add_custom_command(
    TARGET triangles
    POST_BUILD
    COMMAND
        "${CMAKE_COMMAND}" -E copy_if_different
        "${CMAKE_CURRENT_LIST_DIR}/../bin/media/shaders/primitive_restart/primitive_restart.fs.glsl"
        "${CMAKE_CURRENT_LIST_DIR}/../bin/media/shaders/primitive_restart/primitive_restart.vs.glsl"
        $<TARGET_FILE_DIR:triangles>
    VERBATIM
)
