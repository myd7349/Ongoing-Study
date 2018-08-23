cmake_minimum_required (VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake")
endif()

project(data_rate_unit_unittest)

enable_testing()

find_package(GTest REQUIRED)

add_executable(data_rate_unit_unittest
    "data_rate_unit_unittest.cpp"
    )

target_link_libraries(data_rate_unit_unittest GTest::GTest GTest::Main)

add_test(AllTests data_rate_unit_unittest)
