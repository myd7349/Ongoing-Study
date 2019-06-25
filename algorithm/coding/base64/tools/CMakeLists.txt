add_executable(base64_cli base64_cli.c)
set_target_properties(base64_cli PROPERTIES OUTPUT_NAME base64)
target_link_libraries(base64_cli base64)
