include(GNUInstallDirs)

set(headers
    ${CMAKE_SOURCE_DIR}/include/libfoo/foo.h
)

set(sources
    ${CMAKE_SOURCE_DIR}/src/foo.c
)

if (BUILD_STATIC_LIBS)
    add_library(${PROJECT_NAME}_static STATIC ${headers} ${sources})
    set_target_properties(${PROJECT_NAME}_static
        PROPERTIES
            PREFIX ""
            PUBLIC_HEADER "${headers}"
    )

    target_include_directories(${PROJECT_NAME}_static
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
    )

    if (WIN32)
        target_compile_definitions(${PROJECT_NAME}_static
            PUBLIC FOO_STATIC_LIB
        )
    endif ()

    install(
        TARGETS ${PROJECT_NAME}_static
        EXPORT ${PROJECT_NAME}-config
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    )
endif ()

if (BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} SHARED ${headers} ${sources})
    set_target_properties(${PROJECT_NAME}
        PROPERTIES
            PREFIX ""
            PUBLIC_HEADER "${headers}"
    )
    target_include_directories(${PROJECT_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
    )

    if (WIN32)
        target_compile_definitions(${PROJECT_NAME}
            PRIVATE $<BUILD_INTERFACE:FOO_EXPORTS>
            INTERFACE $<INSTALL_INTERFACE:FOO_SHARED_LIB>
        )
    endif ()

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
# https://cgold.readthedocs.io/en/latest/tutorials/libraries/static-shared.html
# https://stackoverflow.com/questions/21852817/cmake-how-to-create-alias-for-installing-different-targets
