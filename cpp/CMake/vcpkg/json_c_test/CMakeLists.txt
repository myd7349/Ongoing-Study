cmake_minimum_required(VERSION 3.8)

project(json_c_test C)

option(JSON_C_SUBPROJECT_TEST "Use json-c as a subproject." OFF)

if (JSON_C_SUBPROJECT_TEST)
    find_package(Git REQUIRED)

    execute_process(
        COMMAND ${GIT_EXECUTABLE} clone https://github.com/json-c/json-c
        OUTPUT_VARIABLE REV_LIST_STR
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        ENCODING AUTO
    )

    add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/json-c EXCLUDE_FROM_ALL)
else (JSON_C_SUBPROJECT_TEST)
    find_package(json-c CONFIG REQUIRED)
endif (JSON_C_SUBPROJECT_TEST)


add_executable(json_c_test json_c_test.c)
if (MSVC)
    target_compile_definitions(json_c_test PRIVATE  _CRT_SECURE_NO_WARNINGS)
endif (MSVC)

if (JSON_C_SUBPROJECT_TEST)
    target_link_libraries(json_c_test PRIVATE json-c)
else (JSON_C_SUBPROJECT_TEST)
    target_link_libraries(json_c_test PRIVATE json-c::json-c)
endif (JSON_C_SUBPROJECT_TEST)

add_custom_command(TARGET json_c_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_LIST_DIR}/example.json"
        $<TARGET_FILE_DIR:json_c_test>
)


# References:
# https://github.com/json-c/json-c/pull/450
