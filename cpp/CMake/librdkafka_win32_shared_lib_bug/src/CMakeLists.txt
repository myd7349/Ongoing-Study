include(GNUInstallDirs)

option(BUILD_SHARED_LIBS "Build shared library." OFF)
option(REPRODUCE_WIN32_SHARED_LIBS_BUG "Reproduce Win32 shared library bug." ON)

set(headers
    ${CMAKE_SOURCE_DIR}/include/foo/foo.h
)

set(sources
    ${CMAKE_SOURCE_DIR}/src/foo.cpp
)

add_library(${PROJECT_NAME} ${headers} ${sources})

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER ${headers})

target_include_directories(${PROJECT_NAME}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

if (BUILD_SHARED_LIBS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LIBRDKAFKACPP_EXPORTS)
    if (REPRODUCE_WIN32_SHARED_LIBS_BUG)
        if (WIN32)
            target_compile_definitions(${PROJECT_NAME} INTERFACE LIBRDKAFKACPP_EXPORTS=0)
        endif ()
    endif ()
else ()
    target_compile_definitions(${PROJECT_NAME} PUBLIC LIBRDKAFKA_STATICLIB)
endif ()

install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT ${PROJECT_NAME}-config
    FILE ${PROJECT_NAME}-config.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)


# References:
# https://github.com/edenhill/librdkafka/blob/master/src/CMakeLists.txt
# https://github.com/edenhill/librdkafka/blob/master/src-cpp/CMakeLists.txt
