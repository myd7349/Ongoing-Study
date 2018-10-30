cmake_minimum_required(VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

project(hello_qt CXX)

find_package(Qt5Widgets CONFIG REQUIRED)

add_executable(hello_qt "hello_qt.cpp")

target_link_libraries(hello_qt PRIVATE Qt5::Widgets Qt5::WidgetsPrivate)
