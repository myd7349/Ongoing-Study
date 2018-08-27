cmake_minimum_required(VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake")
endif()

project(getprogname_unittest)

add_definitions(-D_CRT_SECURE_NO_WARNINGS=1)

enable_testing()

find_package(GTest REQUIRED)

add_executable(getprogname_unittest
    "getprogname_unittest.cpp"
	"../getprogname.c"
    "../../algorithm/string/stringview.c"
    "../../algorithm/string/substr.c"
    )

target_link_libraries(getprogname_unittest GTest::GTest GTest::Main)

add_test(AllTests getprogname_unittest)
