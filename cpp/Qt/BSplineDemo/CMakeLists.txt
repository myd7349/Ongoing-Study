cmake_minimum_required(VERSION 3.8)

project(BSplineDemo C CXX)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)

option(USE_EXTERNAL_TINYSPLINE "Use external tinyspline" OFF)

if (USE_EXTERNAL_TINYSPLINE)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})
    find_package(TinySpline REQUIRED)

    message(STATUS "TINYSPLINE_INCLUDE_DIRS: ${TINYSPLINE_INCLUDE_DIRS}")
    message(STATUS "TINYSPLINE_LIBRARIES: ${TINYSPLINE_LIBRARIES}")
    message(STATUS "TINYSPLINECPP_LIBRARIES: ${TINYSPLINECPP_LIBRARIES}")
else ()
    include(FetchContent)
    
    FetchContent_Declare(
        tinyspline
        GIT_REPOSITORY https://github.com/msteinbeck/tinyspline
        GIT_TAG        1bf5ac27105bb9afc1dc7ef1f1949c6c67334e11
    )

    FetchContent_GetProperties(tinyspline)
    if (NOT tinyspline_POPULATED)
        FetchContent_Populate(tinyspline)
        add_subdirectory(${tinyspline_SOURCE_DIR} ${tinyspline_BINARY_DIR})
    endif ()

    set(TINYSPLINE_LIBRARIES tinyspline_static)
    set(TINYSPLINECPP_LIBRARIES tinysplinecpp_static)
endif ()

add_executable(
    BSplineDemo
    main.cpp
    mainwindow.cpp
    knotsequence.cpp
    KnotSequenceMouseAction.cpp
)

target_include_directories(BSplineDemo PRIVATE "${TINYSPLINE_INCLUDE_DIRS}")

target_link_libraries(
    BSplineDemo
    PRIVATE
        Qt6::Widgets
        ${TINYSPLINE_LIBRARIES}
        ${TINYSPLINECPP_LIBRARIES}
)


if (WIN32 AND USE_EXTERNAL_TINYSPLINE)
    message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        get_filename_component(TINYSPLINE_DLL_DIR "${TINYSPLINE_LIBRARY_DEBUG}" DIRECTORY)
        message(STATUS "TINYSPLINE_DLL_DIR: ${TINYSPLINE_DLL_DIR}")
    else ()
        get_filename_component(TINYSPLINE_DLL_DIR "${TINYSPLINE_LIBRARY_RELEASE}" DIRECTORY)
    endif ()
    get_filename_component(TINYSPLINE_DLL_DIR "${TINYSPLINE_DLL_DIR}" DIRECTORY)

    message(STATUS "TINYSPLINE_LIBRARY_DEBUG: ${TINYSPLINE_LIBRARY_DEBUG}")
    message(STATUS "TINYSPLINE_LIBRARY_RELEASE: ${TINYSPLINE_LIBRARY_RELEASE}")
    message(STATUS "TINYSPLINE_DLL_DIR: ${TINYSPLINE_DLL_DIR}")

    foreach (dll_name tinyspline tinysplinecpp tinysplined tinysplinecppd)
        if (EXISTS "${TINYSPLINE_DLL_DIR}/bin/${dll_name}.dll")
            add_custom_command(
                TARGET BSplineDemo
                POST_BUILD
                COMMAND "${CMAKE_COMMAND}"
                ARGS
                    -E
                    copy_if_different
                    "${TINYSPLINE_DLL_DIR}/bin/${dll_name}.dll"
                    $<TARGET_FILE_DIR:BSplineDemo>
                VERBATIM
            )
        endif ()
    endforeach ()
endif ()


# References:
# https://stackoverflow.com/questions/25875255/cmake-qt5-qt5-wrap-ui-not-generating-ui-header-files
# https://gist.github.com/optimalistel/dab127b58883b002a5ad
# https://stackoverflow.com/questions/35847655/when-should-i-quote-variables
