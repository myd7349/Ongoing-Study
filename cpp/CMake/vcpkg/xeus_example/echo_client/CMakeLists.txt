set(ECHO_CLIENT_SOURCES
    echo_client.cpp
    echo_client.hpp
    main.cpp)

add_executable(echo_client ${ECHO_CLIENT_SOURCES})
target_link_libraries(echo_client xeus)

target_compile_features(echo_client PRIVATE cxx_std_11)

set(CONNECTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../echo_kernel/connection.json)

add_custom_command(TARGET echo_client POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E
                   copy "${CONNECTION_FILE}" "$<TARGET_FILE_DIR:echo_client>")
