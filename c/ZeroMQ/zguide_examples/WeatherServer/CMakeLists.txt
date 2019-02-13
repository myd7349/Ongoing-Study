cmake_minimum_required(VERSION 3.8)

project(weather LANGUAGES C)

find_package(ZeroMQ CONFIG REQUIRED)

add_executable(wuclient "WeatherClient/wuclient.c")
target_link_libraries(wuclient PRIVATE libzmq libzmq-static)
target_include_directories(wuclient PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../)

add_executable(wuserver "WeatherServer/wuserver.c")
target_link_libraries(wuserver PRIVATE libzmq libzmq-static)
target_include_directories(wuserver PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../)

# References:
# https://stackoverflow.com/questions/13703647/how-to-properly-add-include-directories-with-cmake
