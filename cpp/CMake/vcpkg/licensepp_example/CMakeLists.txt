cmake_minimum_required(VERSION 3.9)

project(licensepp_example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(licensepp CONFIG REQUIRED)

add_executable(licensepp_example licensepp_example.cpp)
target_include_directories(licensepp_example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(licensepp_example PRIVATE licensepp-lib)
