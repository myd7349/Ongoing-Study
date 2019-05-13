cmake_minimum_required(VERSION 3.12)

project(pfultz2_linq_test LANGUAGES CXX)

find_package(Boost
    1.68.0
    REQUIRED
    COMPONENTS
        unit_test_framework
)

message(STATUS "Boost_UNIT_TEST_FRAMEWORK_LIBRARY: ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}")

find_package(linq CONFIG REQUIRED)

file(DOWNLOAD
    https://raw.githubusercontent.com/pfultz2/Linq/master/test.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/test.cpp
)

option(USE_MSVC_STATIC_RUNTIME "Use static version of MSVC CRT." OFF)

if (USE_MSVC_STATIC_RUNTIME)
    if (MSVC)
        foreach(flag_var
            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
            if(${flag_var} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
            endif(${flag_var} MATCHES "/MD")
        endforeach(flag_var)
    endif (MSVC)
endif (USE_MSVC_STATIC_RUNTIME)

include(CTest)

if (BUILD_TESTING)
    add_executable(linq_test ${CMAKE_CURRENT_BINARY_DIR}/test.cpp)
    #target_include_directories(linq_test PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(linq_test PRIVATE linq::linq Boost::boost Boost::unit_test_framework )

    add_test(NAME linq_test COMMAND linq_test)
endif (BUILD_TESTING)


# References:
# https://stackoverflow.com/questions/3897839/how-to-link-c-program-with-boost-using-cmake
# https://github.com/Kitware/CMake/blob/master/Modules/FindBoost.cmake
# https://stackoverflow.com/questions/9881288/compiling-a-boost-test-with-cmake
# https://stackoverflow.com/questions/4299326/how-can-i-use-boost-test-in-a-cmake-based-project
# http://neyasystems.com/an-engineers-guide-to-unit-testing-cmake-and-boost-unit-tests/
# https://stackoverflow.com/questions/42123509/cmake-finds-boost-but-the-imported-targets-not-available-for-boost-version/42124857#42124857
# https://stackoverflow.com/questions/42123509/cmake-finds-boost-but-the-imported-targets-not-available-for-boost-version/42124857#42124857
# https://stackoverflow.com/questions/50468620/what-does-enable-testing-do-in-cmake
# https://cmake.org/cmake/help/latest/command/enable_testing.html
# https://stackoverflow.com/questions/9881288/compiling-a-boost-test-with-cmake
