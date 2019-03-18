cmake_minimum_required(VERSION 3.8)

project(prefix_and_suffix CXX)

if (BUILD_SHARED_LIBS)
    message(STATUS "-- Build shared libs.")
endif ()

foreach (var
    CMAKE_SHARED_LIBRARY_PREFIX
    CMAKE_SHARED_LIBRARY_SUFFIX
    CMAKE_STATIC_LIBRARY_PREFIX
    CMAKE_STATIC_LIBRARY_SUFFIX
    CMAKE_IMPORT_LIBRARY_PREFIX
    CMAKE_IMPORT_LIBRARY_SUFFIX
    )
    message(STATUS ">> ${var} ${${var}}")
endforeach ()


# References:
# cmocka
