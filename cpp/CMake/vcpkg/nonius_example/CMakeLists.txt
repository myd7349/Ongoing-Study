cmake_minimum_required(VERSION 3.9)

project(nonius_example CXX)

find_path(
    NONIUS_INCLUDE_DIRS
    NAMES nonius/nonius.h++
)

if (NONIUS_INCLUDE_DIRS)
    message(STATUS "NONIUS_INCLUDE_DIRS: ${NONIUS_INCLUDE_DIRS}")
else ()
    message(FATAL_ERROR "Couldn't find Nonius.")
endif ()

set(examples
    example1.cpp
    example2.cpp
    example3.cpp
    example4.cpp
    example5.cpp
    example6.cpp
    example7.cpp
)

foreach (example_src ${examples})
    get_filename_component(example_title ${example_src} NAME_WE)
    
    add_executable(${example_title} ${CMAKE_CURRENT_LIST_DIR}/${example_src})
    target_include_directories(${example_title} PRIVATE ${NONIUS_INCLUDE_DIRS})
endforeach ()
