cmake_minimum_required (VERSION 3.8)

project(circular_buffer_unittest)

enable_testing()

find_package(GTest REQUIRED)

add_executable(circular_buffer_unittest
    "circular_buffer_unittest.cpp"
	"../circular_buffer.c")

target_link_libraries(circular_buffer_unittest GTest::GTest GTest::Main)

add_test(CircbufTests circular_buffer_unittest)
