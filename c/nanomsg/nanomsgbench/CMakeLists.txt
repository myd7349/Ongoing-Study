cmake_minimum_required(VERSION 3.8)

project(nanomsgbench C)

add_executable(nanomsgbench_client
    "nanomsgbench_client.c"
    "../../high_timer.c"
    )
add_executable(nanomsgbench_server
    "nanomsgbench_server.c"
    "../../high_timer.c"
    )

add_definitions(-D_CRT_SECURE_NO_WARNINGS=1 -D_CRT_NONSTDC_NO_DEPRECATE=1)

# Currently, find_package does work with `nanomsg` when using vcpkg.
if(WIN32)
    target_include_directories(nanomsgbench_client PRIVATE "$ENV{VCPKG_DIR}/installed/x86-windows/include")
    target_link_libraries(nanomsgbench_client PRIVATE "$ENV{VCPKG_DIR}/installed/x86-windows/lib/nanomsg.lib")
    
    add_custom_command(TARGET nanomsgbench_client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$ENV{VCPKG_DIR}/installed/x86-windows/bin/nanomsg.dll"
            $<TARGET_FILE_DIR:nanomsgbench_client>)

    target_include_directories(nanomsgbench_server PRIVATE "$ENV{VCPKG_DIR}/installed/x86-windows/include")
    target_link_libraries(nanomsgbench_server PRIVATE "$ENV{VCPKG_DIR}/installed/x86-windows/lib/nanomsg.lib")
    
    add_custom_command(TARGET nanomsgbench_server POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$ENV{VCPKG_DIR}/installed/x86-windows/bin/nanomsg.dll"
            $<TARGET_FILE_DIR:nanomsgbench_server>)
endif()

# References:
# https://stackoverflow.com/questions/34937671/cmake-how-to-check-if-preprocessor-is-defined
