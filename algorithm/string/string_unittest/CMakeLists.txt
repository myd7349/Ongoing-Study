cmake_minimum_required (VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake")
endif()

project(string_unittest)

add_definitions(-D_CRT_SECURE_NO_WARNINGS=1)

enable_testing()

find_package(GTest REQUIRED)

add_executable(string_unittest
    "string_unittest.cpp"
    "../stringview.c"
    "../substr.c"
    )

target_link_libraries(string_unittest GTest::GTest GTest::Main)

add_test(AllTests string_unittest)
