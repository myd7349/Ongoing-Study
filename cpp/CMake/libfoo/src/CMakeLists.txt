include(GNUInstallDirs)

set(headers
    ${CMAKE_SOURCE_DIR}/include/foo/foo.h
)

set(sources
    ${CMAKE_SOURCE_DIR}/src/foo.c
)

if (BUILD_STATIC_LIBS)
    add_library(${PROJECT_NAME}_static STATIC ${headers} ${sources})
    set_target_properties(${PROJECT_NAME}_static
        PROPERTIES
            PUBLIC_HEADER "${headers}"
            PREFIX ""
            OUTPUT_NAME "lib${PROJECT_NAME}_static"
    )

    target_include_directories(${PROJECT_NAME}_static
        PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )

    install(
        TARGETS ${PROJECT_NAME}_static
        EXPORT ${PROJECT_NAME}-config
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    )
endif ()

if (BUILD_SHARED_LIBS)
    if (WIN32)
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS YES CACHE BOOL "Export all symbols")
    endif ()

    add_library(${PROJECT_NAME} SHARED ${headers} ${sources})
    set_target_properties(${PROJECT_NAME}
        PROPERTIES
            PUBLIC_HEADER "${headers}"
            PREFIX ""
            OUTPUT_NAME "lib${PROJECT_NAME}"
    )
    target_include_directories(${PROJECT_NAME}
        PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
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
    FILE ${PROJECT_NAME}-config.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)


# References:
# https://cgold.readthedocs.io/en/latest/tutorials/libraries/static-shared.html
# https://stackoverflow.com/questions/21852817/cmake-how-to-create-alias-for-installing-different-targets
