cmake_minimum_required(VERSION 3.8)

project(BSplineDemo C CXX)

include(FetchContent)

find_package(Qt5Widgets CONFIG REQUIRED)

set(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)

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
        tinyspline_static
        tinysplinecpp_static
)


# References:
# https://stackoverflow.com/questions/25875255/cmake-qt5-qt5-wrap-ui-not-generating-ui-header-files
# https://gist.github.com/optimalistel/dab127b58883b002a5ad
# https://stackoverflow.com/questions/35847655/when-should-i-quote-variables
