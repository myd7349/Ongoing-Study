cmake_minimum_required(VERSION 3.8)

project(FindPeaksTest CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Python3 COMPONENTS Interpreter Development)
find_path(MATPLOTLIBCPP_INCLUDE_DIR NAMES matplotlibcpp.h)

message(STATUS "Python3_LIBRARIES: ${Python3_LIBRARIES}")
message(STATUS "Python3_LIBRARY_RELEASE: ${Python3_LIBRARY_RELEASE}")
message(STATUS "Python3_SITELIB: ${Python3_SITELIB}")
message(STATUS "Python3_EXECUTABLE: ${Python3_EXECUTABLE}")

add_executable(FindPeaksTest "FindPeaksTest.cpp" "../FindPeaks.cpp")

set(PYTHONHOME ${Python3_EXECUTABLE})
get_filename_component(PYTHONHOME ${PYTHONHOME} DIRECTORY)
if (WIN32)
    string(REPLACE "\\" "\\\\" PYTHONHOME ${PYTHONHOME})
endif ()
target_compile_definitions(FindPeaksTest PRIVATE PYTHONHOME=\"${PYTHONHOME}\")

target_include_directories(FindPeaksTest PRIVATE ${MATPLOTLIBCPP_INCLUDE_DIR})

# On my PC, only python36.lib is available, but it tries to link to python36_d.lib.
target_link_libraries(FindPeaksTest PRIVATE Python3::Python)

# References:
# https://stackoverflow.com/questions/690223/how-to-retrieve-a-user-environment-variable-in-cmake-windows
# https://stackoverflow.com/questions/35029277/how-to-modify-environment-variables-passed-to-custom-cmake-target
# https://stackoverflow.com/questions/10675315/setting-pythonpath-and-pythonhome
