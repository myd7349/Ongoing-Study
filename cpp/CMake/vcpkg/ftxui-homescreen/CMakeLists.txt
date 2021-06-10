cmake_minimum_required(VERSION 3.8)

project(ftxui-homescreen LANGUAGES CXX)

find_package(ftxui CONFIG REQUIRED)

set(url "https://raw.githubusercontent.com/ArthurSonzogni/FTXUI/master/examples/component/homescreen.cpp")

if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/homescreen.cpp")
    file(DOWNLOAD ${url} "${CMAKE_CURRENT_BINARY_DIR}/homescreen.cpp")
endif()

add_executable(ftxui-homescreen "${CMAKE_CURRENT_BINARY_DIR}/homescreen.cpp")
target_link_libraries(ftxui-homescreen PRIVATE ftxui::dom ftxui::screen ftxui::component)
target_compile_features(ftxui-homescreen PRIVATE cxx_std_17)
