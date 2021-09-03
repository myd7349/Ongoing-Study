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

set(format7zr_output_lib "${lzma_SOURCE_DIR}/CPP/7zip/Bundles/Format7zR/x64/7zra.lib")
add_custom_command(
    OUTPUT "${format7zr_output_lib}"
    COMMAND "${NMAKE}"
    ARGS /f makefile
    WORKING_DIRECTORY "${lzma_SOURCE_DIR}/CPP/7zip/Bundles/Format7zR"
    VERBATIM
)
add_custom_target(build_format7zr DEPENDS "${format7zr_output_lib}")

add_library(
    Q7Zip
    STATIC
    Q7Zip.cpp
    "${lzma_SOURCE_DIR}/CPP/Common/C_FileIO.cpp"
    "${lzma_SOURCE_DIR}/CPP/7zip/Common/FileStreams.cpp"
    "${lzma_SOURCE_DIR}/CPP/7zip/Common/FileStreams.cpp"
    "${lzma_SOURCE_DIR}/CPP/Common/IntToString.cpp"
    "${lzma_SOURCE_DIR}/CPP/Common/MyString.cpp"
    "${lzma_SOURCE_DIR}/CPP/Common/StringConvert.cpp"
    "${lzma_SOURCE_DIR}/CPP/Windows/FileDir.cpp"
    "${lzma_SOURCE_DIR}/CPP/Windows/FileFind.cpp"
    "${lzma_SOURCE_DIR}/CPP/Windows/FileIO.cpp"
    "${lzma_SOURCE_DIR}/CPP/Windows/FileName.cpp"
    "${lzma_SOURCE_DIR}/CPP/Windows/PropVariant.cpp"

)

add_dependencies(Q7Zip build_format7zr)

target_include_directories(
    Q7Zip
    PRIVATE
        "${lzma_SOURCE_DIR}"
        "${lzma_SOURCE_DIR}/CPP"
)

target_compile_definitions(
    Q7Zip
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:
            _CRT_NONSTDC_NO_DEPRECATE
            _CRT_SECURE_NO_WARNINGS
            /wd4267
        >
)

target_link_libraries(
    Q7Zip
    PUBLIC
        Qt6::Core
        "${format7zr_output_lib}"
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


# References:
# https://cmake.org/cmake/help/latest/policy/CMP0058.html
