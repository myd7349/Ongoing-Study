cmake_minimum_required (VERSION 3.8)

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_DIR}\\scripts\\buildsystems\\vcpkg.cmake")

project(isprime_unittest)

enable_testing()

find_package(GTest REQUIRED)

if(GTEST_FOUND)
    message(STATUS ${GTEST_INCLUDE_DIRS})
	message(STATUS ${GTEST_LIBRARIES})
	message(STATUS ${GTEST_MAIN_LIBRARIES})
    message(STATUS ${GTEST_LIBRARY})
	message(STATUS ${GTEST_MAIN_LIBRARY})
else(GTEST_FOUND)
    message(FATAL_ERROR "gtest library not found")
endif(GTEST_FOUND)

add_executable(isprime_unittest
    "isprime_unittest.cpp"
	"../../../../algorithm/math/NumberTheory/is_prime.cpp")

target_link_libraries(isprime_unittest GTest::GTest GTest::Main)

add_test(AllTests isprime_unittest)

# References:
# FindGTest.cmake
# https://github.com/queezythegreat/arduino-cmake/issues/38
