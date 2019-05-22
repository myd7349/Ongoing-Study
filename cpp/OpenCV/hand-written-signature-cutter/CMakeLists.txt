cmake_minimum_required(VERSION 3.8)

project(hand-written-signature-cutter CXX)

find_package(OpenCV REQUIRED)
find_package(tinyfiledialogs CONFIG REQUIRED)

add_executable(hand-written-signature-cutter hand-written-signature-cutter.cpp)
target_include_directories(hand-written-signature-cutter PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(hand-written-signature-cutter PRIVATE ${OpenCV_LIBS} tinyfiledialogs::tinyfiledialogs)
