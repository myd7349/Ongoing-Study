cmake_minimum_required(VERSION 3.8)
project(hello-eigen CXX)

find_package(Eigen3 CONFIG REQUIRED)

add_executable(ex01-hello-eigen ex01-hello-eigen.cpp)
target_link_libraries(ex01-hello-eigen PRIVATE Eigen3::Eigen)

add_executable(ex02-matrices-vs-vectors ex02-matrices-vs-vectors.cpp)
target_link_libraries(ex02-matrices-vs-vectors PRIVATE Eigen3::Eigen)

add_executable(ex03-arithmetic ex03-arithmetic.cpp)
target_link_libraries(ex03-arithmetic PRIVATE Eigen3::Eigen)
