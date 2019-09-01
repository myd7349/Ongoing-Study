cmake_minimum_required(VERSION 3.9)

project(quantlib_tests CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

find_package(
    Boost
    REQUIRED
    COMPONENTS
        date_time
)
find_package(QuantLib REQUIRED)

option(MSVC_STATIC_RUNTIME "Using MSVC static runtime" OFF)

message(STATUS "QUANTLIB_INCLUDE_DIRS: ${QUANTLIB_INCLUDE_DIRS}")
message(STATUS "QUANTLIB_LIBRARIES: ${QUANTLIB_LIBRARIES}")

if (MSVC AND MSVC_STATIC_RUNTIME)
    foreach (flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        if (${flag_var} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endif (${flag_var} MATCHES "/MD")
    endforeach ()
endif ()

add_executable(quantlib_tests quantlib_tests.cpp)
target_include_directories(quantlib_tests PRIVATE ${QUANTLIB_INCLUDE_DIRS})
target_link_libraries(
    quantlib_tests
    PRIVATE
        Boost::date_time
        ${QUANTLIB_LIBRARIES}
)
