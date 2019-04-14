project(examples)

add_executable(models_rlgl_solar_system models/models_rlgl_solar_system.c)

target_include_directories(models_rlgl_solar_system PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(models_rlgl_solar_system raylib)

execute_process(
    COMMAND ${CMAKE_C_COMPILER} -E ${CMAKE_CURRENT_SOURCE_DIR}/models/models_rlgl_solar_system.c -I ${CMAKE_CURRENT_LIST_DIR}/../src
)
