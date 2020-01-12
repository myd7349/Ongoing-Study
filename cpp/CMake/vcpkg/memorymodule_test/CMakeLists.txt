cmake_minimum_required(VERSION 3.9)

project(memorymodule_tests LANGUAGES C)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

find_package(MemoryModule REQUIRED)

option(ENABLE_UNICODE "Enable unicode support" ON)

add_library(mylib SHARED mylib.c)

add_executable(memorymodule_test memorymodule_test.c)
target_link_libraries(memorymodule_test PRIVATE MemoryModule::MemoryModule)
if(ENABLE_UNICODE)
    target_compile_definitions(memorymodule_test PRIVATE _UNICODE UNICODE)
endif()

add_custom_command(
    TARGET memorymodule_test
    POST_BUILD
    COMMAND
        "${CMAKE_COMMAND}" -E copy_if_different
        $<TARGET_FILE:mylib>
        $<TARGET_FILE_DIR:memorymodule_test>
    VERBATIM
)
