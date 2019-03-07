cmake_minimum_required(VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

project(QuadraticDemo CXX)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/..)

find_package(Qt5PrintSupport CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(QCustomPlot REQUIRED MODULE)

if(NOT QCustomPlot_FOUND)
    message(FATAL_ERROR ">>> QCustomPlot not found.")
endif()

message(STATUS ">>> QCustomPlot_INCLUDE_DIRS: ${QCustomPlot_INCLUDE_DIRS}")
message(STATUS ">>> QCustomPlot_LIBRARIES: ${QCustomPlot_LIBRARIES}")

option(USE_STATIC_CRT "Use static version of CRT." OFF)

if (USE_STATIC_CRT)
    if (MSVC)
        foreach(flag_var
            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
            if(${flag_var} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
            endif(${flag_var} MATCHES "/MD")
        endforeach(flag_var)
    endif (MSVC)

    find_package(harfbuzz CONFIG REQUIRED)

    find_library(
        PCRE_LIBRARY
        NAMES pcre2-16d
    )

    message(STATUS ">>> PCRE_LIBRARY: ${PCRE_LIBRARY}")

    find_package(double-conversion CONFIG REQUIRED)
endif ()

add_executable(QuadraticDemo "QuadraticDemo.cpp")

target_include_directories(QuadraticDemo PRIVATE ${QCustomPlot_INCLUDE_DIRS})

target_link_libraries(
    QuadraticDemo
    PRIVATE
    Qt5::PrintSupport
    Qt5::Widgets
    Qt5::WidgetsPrivate
    ${QCustomPlot_LIBRARIES}
)

if (USE_STATIC_CRT)
    target_link_libraries(
        QuadraticDemo
        PRIVATE
        harfbuzz::harfbuzz
        ${PCRE_LIBRARY}
        double-conversion::double-conversion
    )

    if (CMAKE_HOST_WIN32)
        target_link_libraries(
            QuadraticDemo
            PRIVATE
            Ws2_32
            Version
            Netapi32
            Userenv
            Winmm
        )
    endif ()
endif ()

get_filename_component(_root_dir ${QCustomPlot_INCLUDE_DIRS} DIRECTORY)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(_dll ${_root_dir}/debug/bin/qcustomplotd2.dll)
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
    set(_dll ${_root_dir}/bin/qcustomplot2.dll)
endif()

if(EXISTS ${_dll})
    message(STATUS ">>> Copying dll file: ${_dll}")
    add_custom_command(TARGET QuadraticDemo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${_dll}
        $<TARGET_FILE_DIR:QuadraticDemo>)
endif()

# References:
# https://github.com/pabloariasal/modern-cmake-sample/blob/master/libjsonutils/CMakeLists.txt
# https://stackoverflow.com/questions/7724569/debug-vs-release-in-cmake
# https://stackoverflow.com/questions/13067401/cmake-check-that-a-local-file-exists
