cmake_minimum_required(VERSION 3.9)

project(iniparser_example C)

find_package(unofficial-iniparser CONFIG REQUIRED)

add_executable(iniparser_example iniparser_example.c)
target_link_libraries(iniparser_example PRIVATE unofficial::iniparser::iniparser)

add_custom_command(
    TARGET iniparser_example
    POST_BUILD COMMAND
        "${CMAKE_COMMAND}" -E copy_if_different
        "${CMAKE_CURRENT_LIST_DIR}/account.ini"
        $<TARGET_FILE_DIR:iniparser_example>
)
