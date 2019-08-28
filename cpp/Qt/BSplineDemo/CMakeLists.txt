cmake_minimum_required(VERSION 3.8)

project(BSplineDemo C CXX)

find_package(Qt5Widgets CONFIG REQUIRED)

find_path(TINYSPLINE_INCLUDE_DIRS NAMES tinysplinecpp.h)
find_library(TINYSPLINE_LIBRARY NAMES libtinyspline)
find_library(TINYSPLINECPP_LIBRARY NAMES libtinysplinecpp)

set(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)

if (MSVC)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
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
        Qt5::Widgets
        Qt5::WidgetsPrivate
        "${TINYSPLINE_LIBRARY}"
        "${TINYSPLINECPP_LIBRARY}"
)

if (WIN32)
    get_filename_component(TINYSPLINE_DLL_DIR "${TINYSPLINE_LIBRARY}" DIRECTORY)
    get_filename_component(TINYSPLINE_DLL_DIR "${TINYSPLINE_DLL_DIR}" DIRECTORY)

    foreach (dll_name tinyspline tinysplinecpp)
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
