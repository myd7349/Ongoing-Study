set(ECHO_KERNEL_SOURCES
    echo_interpreter.cpp
    echo_interpreter.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../echo_client/echo_client.cpp
    main.cpp)

add_executable(echo_kernel ${ECHO_KERNEL_SOURCES})
target_link_libraries(echo_kernel xeus)

target_include_directories(echo_kernel PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../echo_client>
)

target_compile_features(echo_kernel PRIVATE cxx_std_11)

set(CONNECTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/connection.json)
set(KERNEL_FILE ${CMAKE_CURRENT_SOURCE_DIR}/kernel.json)

add_custom_command(TARGET echo_kernel POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E
                   copy "${CONNECTION_FILE}" "$<TARGET_FILE_DIR:echo_kernel>")

add_custom_command(TARGET echo_kernel POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E
                   copy "${KERNEL_FILE}" "$<TARGET_FILE_DIR:echo_kernel>")
