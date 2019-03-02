cmake_minimum_required(VERSION 3.9)

project(MiniBrowser CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Qml CONFIG REQUIRED)
find_package(Qt5Quick CONFIG REQUIRED)
find_package(Qt5WebView CONFIG REQUIRED)

add_executable(MiniBrowser
    "main.cpp"
    "qml.qrc"
)

target_link_libraries(MiniBrowser
    PRIVATE
    Qt5::Core
    Qt5::Qml
    Qt5::Quick
    Qt5::WebView
)

# References:
# https://cmake.org/cmake/help/latest/manual/cmake-qt.7.html#manual:cmake-qt(7)
# https://doc.qt.io/qt-5/cmake-manual.html
# https://stackoverflow.com/questions/29468413/qt-resources-files-with-cmake-and-autorcc
# https://github.com/apriorit/MinimalQml
# https://cmake.org/cmake/help/v3.0/manual/cmake-qt.7.html
# https://www.apriorit.com/dev-blog/475-qt-qml-with-cmake
