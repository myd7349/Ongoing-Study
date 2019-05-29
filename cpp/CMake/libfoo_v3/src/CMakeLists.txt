include(GenerateExportHeader)
include(GNUInstallDirs)

set(headers
    ${CMAKE_SOURCE_DIR}/include/libfoo/foo.h
)

set(sources
    ${CMAKE_SOURCE_DIR}/src/foo.c
)

if (BUILD_STATIC_LIBS)
    add_library(${PROJECT_NAME}_static STATIC ${headers} ${sources})
endif ()

if (BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} SHARED ${headers} ${sources})
    set(target ${PROJECT_NAME})
else ()
    set(target ${PROJECT_NAME}_static)
endif ()

generate_export_header(
    ${target}
    BASE_NAME FOO
    EXPORT_MACRO_NAME FOO_API
    EXPORT_FILE_NAME foo_export.h
    INCLUDE_GUARD_NAME FOO_EXPORT_H_
    STATIC_DEFINE FOO_STATIC_LIB
    DEFINE_NO_DEPRECATED
)

list(APPEND headers ${CMAKE_CURRENT_BINARY_DIR}/foo_export.h)

if (BUILD_STATIC_LIBS)
    set_target_properties(${PROJECT_NAME}_static
        PROPERTIES
            PREFIX ""
            PUBLIC_HEADER "${headers}"
    )

    target_include_directories(${PROJECT_NAME}_static
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
            $<INSTALL_INTERFACE:include>
    )

    target_compile_definitions(${PROJECT_NAME}_static
        PUBLIC FOO_STATIC_LIB
    )

    install(
        TARGETS ${PROJECT_NAME}_static
        EXPORT ${PROJECT_NAME}-config
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    )
endif ()

if (BUILD_SHARED_LIBS)
    set_target_properties(${PROJECT_NAME}
        PROPERTIES
            PREFIX ""
            PUBLIC_HEADER "${headers}"
    )
    target_include_directories(${PROJECT_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
            $<INSTALL_INTERFACE:include>
    )

    install(
        TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}-config
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    )
endif ()

install(
    EXPORT ${PROJECT_NAME}-config
    FILE foo-config.cmake
    NAMESPACE foo::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/foo
)


# References:
# https://github.com/BYVoid/OpenCC/blob/ver.1.0.5/src/CMakeLists.txt
