cmake_minimum_required(VERSION 3.12)

project(FindPeaks CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_PYFINDPEAKS "Build Python binding of FindPeaks." ON)
option(USE_SYSTEM_PYBIND11 "Use system version of pybind11." OFF)

add_library(FindPeaks STATIC FindPeaks.cpp)

if(BUILD_PYFINDPEAKS)
    if(USE_SYSTEM_PYBIND11)
        find_package(pybind11 CONFIG REQUIRED)
    else()
        include(FetchContent)

        FetchContent_Declare(
            pybind11
            GIT_REPOSITORY https://github.com/pybind/pybind11
            GIT_TAG        v2.8.1
        )

        FetchContent_GetProperties(pybind11)
        if(NOT pybind11_POPULATED)
            FetchContent_Populate(pybind11)
            add_subdirectory(${pybind11_SOURCE_DIR} ${pybind11_BINARY_DIR})
        endif()
    endif()

    pybind11_add_module(PyFindPeaks PyFindPeaksImpl.cpp)
    target_link_libraries(PyFindPeaks PRIVATE FindPeaks)

    # There is no need to:
    #find_package(Python COMPONENTS Interpreter Development REQUIRED)
    #target_link_libraries(PyFindPeaks PRIVATE Python::Python)
    # But if you have a 32-bit Python installed, then:
    # cmake -G "Visual Studio 16 2019" -A Win32 ..
endif()


# References:
# https://github.com/BYVoid/OpenCC/blob/2373238bcb1991d2b8269884b0c6df18c130ed53/CMakeLists.txt#L218-L228
# https://pybind11.readthedocs.io/en/stable/compiling.html
# [I have 2 versions of python installed, but cmake is using older version. How do I force cmake to use the newer version?](https://stackoverflow.com/questions/15291500/i-have-2-versions-of-python-installed-but-cmake-is-using-older-version-how-do)
