cmake_minimum_required(VERSION 3.14)

project(Q7Zip LANGUAGES C CXX)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_program(NMAKE NAMES nmake)
if(NOT NMAKE)
    message(FATAL_ERROR "nmake not found.")
else()
    message(STATUS "nmake: ${NMAKE}")
endif()

set(lzma_version 1900)
set(lzma_7z_filename "lzma${lzma_version}.7z")

include(FetchContent)
FetchContent_Populate(
    lzma
    URL "https://www.7-zip.org/a/${lzma_7z_filename}"
    SOURCE_DIR lzma
)

add_library(
    Q7Zip
    SHARED
    Q7Zip.cpp
    "${lzma_SOURCE_DIR}/CPP/Common/C_FileIO.cpp"
    "${lzma_SOURCE_DIR}/CPP/Common/IntToString.cpp"
    "${lzma_SOURCE_DIR}/CPP/Common/MyString.cpp"
    "${lzma_SOURCE_DIR}/CPP/Common/StringConvert.cpp"
    "${lzma_SOURCE_DIR}/CPP/Windows/FileSystem.cpp"
)

target_include_directories(
    Q7Zip
    PUBLIC
        "${lzma_SOURCE_DIR}"
        "${lzma_SOURCE_DIR}/CPP"
)

add_custom_command(
    TARGET Q7Zip
    PRE_BUILD
    COMMAND "${NMAKE}"
    ARGS /f makefile
    WORKING_DIRECTORY "${lzma_SOURCE_DIR}/CPP/7zip/Bundles/Format7zR"
    VERBATIM
)

target_link_libraries(
    Q7Zip
    PUBLIC
        Qt6::Core
)

target_link_libraries(
    Q7Zip
    PUBLIC
        "${lzma_SOURCE_DIR}/CPP/7zip/Bundles/Format7zR/x64/7zra.lib"
)

add_executable(Q7ZipApp main.cpp mainwindow.cpp)
target_link_libraries(Q7ZipApp PRIVATE Qt6::Widgets Q7Zip)

add_custom_command(
    TARGET Q7ZipApp
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}"
    ARGS
        -E
        copy_if_different
        "${lzma_SOURCE_DIR}/CPP/7zip/Bundles/Format7zR/x64/7zra.dll"
        "$<TARGET_FILE_DIR:Q7ZipApp>"
    VERBATIM
)
