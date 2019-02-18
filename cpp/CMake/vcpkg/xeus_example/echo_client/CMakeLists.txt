set(ECHO_CLIENT_SOURCES
    echo_client.cpp
    echo_client.hpp
    main.cpp)

add_executable(echo_client ${ECHO_CLIENT_SOURCES})

if (TARGET xeus)
    message("Found xeus shared library")
    target_link_libraries(echo_client xeus)
endif ()

if (TARGET xeus_static)
    message("Found xeus static library")
    target_link_libraries(echo_client xeus_static)
endif ()

target_compile_features(echo_client PRIVATE cxx_std_11)

if (USE_STATIC_RTL)
    if (MSVC)
        foreach(flag_var
            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
            if(${flag_var} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
            endif(${flag_var} MATCHES "/MD")
        endforeach(flag_var)
    endif (MSVC)
endif ()

set(CONNECTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../echo_kernel/connection.json)

add_custom_command(TARGET echo_client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
    copy "${CONNECTION_FILE}" "$<TARGET_FILE_DIR:echo_client>"
)
