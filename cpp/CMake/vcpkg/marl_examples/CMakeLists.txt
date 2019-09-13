cmake_minimum_required(VERSION 3.9)

project(marl_examples CXX)

find_package(marl CONFIG REQUIRED)

option(MSVC_STATIC_RUNTIME "Using MSVC static runtime" OFF)

if (MSVC AND MSVC_STATIC_RUNTIME)
    foreach (flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        if (${flag_var} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endif (${flag_var} MATCHES "/MD")
    endforeach ()
endif ()

include(FetchContent)

FetchContent_Declare(
    marl
    GIT_REPOSITORY https://github.com/google/marl
    GIT_TAG        fca4771b4cd58f8b16915e4f75aa238354acf7ba
)

FetchContent_GetProperties(marl)
if (NOT marl_POPULATED)
    FetchContent_Populate(marl)
endif ()

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG        33a0d4f6d76a0ed6061e612848532cba82d42870
)

FetchContent_GetProperties(googletest)
if (NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif ()

file(GLOB marl_examples
    ${marl_SOURCE_DIR}/examples/*.cpp
)

foreach (marl_example ${marl_examples})
    get_filename_component(example_name ${marl_example} NAME_WE)
    add_executable(${example_name} ${marl_example})
    target_link_libraries(${example_name} PRIVATE marl::marl)
endforeach ()

file(GLOB marl_tests ${marl_SOURCE_DIR}/src/*_test.cpp)

include(CTest)

foreach (marl_test ${marl_tests})
    get_filename_component(test_name ${marl_test} NAME_WE)
    add_executable(${test_name} ${marl_test})
    target_include_directories(
        ${test_name}
        PRIVATE
            ${googletest_SOURCE_DIR}/googlemock/include
            ${googletest_SOURCE_DIR}/googletest/include
    )
    target_link_libraries(${test_name} PRIVATE marl::marl gtest gtest_main)

    add_test(
        NAME ${test_name}
        COMMAND ${test_name}
        WORKING_DIRECTORY $<TARGET_FILE_DIR:${test_name}>
    )
endforeach ()


# References:
# https://cliutils.gitlab.io/modern-cmake/chapters/testing/googletest.html
