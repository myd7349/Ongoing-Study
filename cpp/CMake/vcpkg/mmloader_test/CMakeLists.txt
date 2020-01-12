cmake_minimum_required(VERSION 3.9)

project(mmloader_tests LANGUAGES C)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

find_package(mmLoader REQUIRED)

add_library(mylib SHARED "${CMAKE_CURRENT_LIST_DIR}/../memorymodule_test/mylib.c")

add_executable(mmloader_test mmloader_test.c)
target_link_libraries(mmloader_test PRIVATE mmLoader::mmLoader)

add_custom_command(
    TARGET mmloader_test
    POST_BUILD
    COMMAND
        "${CMAKE_COMMAND}" -E copy_if_different
        $<TARGET_FILE:mylib>
        $<TARGET_FILE_DIR:mmloader_test>
    VERBATIM
)
