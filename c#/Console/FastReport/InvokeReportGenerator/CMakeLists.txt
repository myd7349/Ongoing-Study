cmake_minimum_required(VERSION 3.15)

project(InvokeReportGenerator LANGUAGES CXX)

find_package(unofficial-tiny-process-library CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(USE_MSVC_STATIC_CRT "Use MSVC static runtime library." OFF)
option(BUILD_REPORT_GENERATOR "Build report generator." OFF)

if(USE_MSVC_STATIC_CRT)
    if(MSVC)
        foreach(flag_var
            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
            if(${flag_var} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
            endif(${flag_var} MATCHES "/MD")
        endforeach(flag_var)
    endif()
endif()

add_executable(InvokeReportGenerator InvokeReportGenerator.cpp)

if(BUILD_REPORT_GENERATOR)
    enable_language(CSharp)

    if (CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(BINARY_FOLDER_SUFFIX x64)
    else ()
        set(BINARY_FOLDER_SUFFIX x86)
    endif ()

    add_subdirectory(
        "${CMAKE_CURRENT_LIST_DIR}/../ReportGenerator"
        "${CMAKE_CURRENT_LIST_DIR}/../ReportGenerator/bin/${BINARY_FOLDER_SUFFIX}/${CMAKE_BUILD_TYPE}"
    )
endif()

if(MSVC)
    target_compile_definitions(
        InvokeReportGenerator
        PRIVATE
            _CRT_SECURE_NO_WARNINGS
            _CRT_NONSTDC_NO_DEPRECATE
    )
endif()

target_link_libraries(
    InvokeReportGenerator
    PRIVATE
        unofficial::tiny-process-library::tiny-process-library
)
