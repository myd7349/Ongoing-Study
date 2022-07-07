cmake_minimum_required(VERSION 3.12)

project(FindPeaks LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(BUILD_SHARED_LIBS AND WIN32)
    set(exports_def_file "${CMAKE_CURRENT_BINARY_DIR}/exports.def")
    set(exports_def_contents
"EXPORTS 
    FindPeaks
")

    file(WRITE "${exports_def_file}" "${exports_def_contents}")

    add_library(FindPeaks
        "${CMAKE_CURRENT_SOURCE_DIR}/../FindPeaks.cpp"
        "${exports_def_file}"
    )
else()
    add_library(FindPeaks "${CMAKE_CURRENT_SOURCE_DIR}/../FindPeaks.cpp")
endif()
