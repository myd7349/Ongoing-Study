cmake_minimum_required(VERSION 3.9)

project(gouraud CXX)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(BINARY_FOLDER_SUFFIX x64)
else()
    set(BINARY_FOLDER_SUFFIX x86)
endif()

add_subdirectory(
    ${CMAKE_CURRENT_LIST_DIR}/../lib
    ${CMAKE_CURRENT_LIST_DIR}/../lib/build/${CMAKE_BUILD_TYPE}_${BINARY_FOLDER_SUFFIX}
)

add_executable(gouraud gouraud.cpp)

target_link_libraries(gouraud PRIVATE libredbook)

if (WIN32)
    set_target_properties(gouraud PROPERTIES WIN32_EXECUTABLE ON)
endif ()

add_custom_command(
    TARGET gouraud
    POST_BUILD
    COMMAND
        "${CMAKE_COMMAND}" -E copy_if_different
        "${CMAKE_CURRENT_LIST_DIR}/../bin/media/shaders/gouraud/gouraud.vert"
        "${CMAKE_CURRENT_LIST_DIR}/../bin/media/shaders/gouraud/gouraud.frag"
        $<TARGET_FILE_DIR:gouraud>
    VERBATIM
)
