cmake_minimum_required(VERSION 3.9)

project(xtensor-fftw-test C CXX)

find_package(FFTW3 CONFIG REQUIRED)
find_path(XTENSOR_FFTW_INCLUDE_DIR xtensor-fftw/basic.hpp)

add_executable(xtensor-fftw-test xtensor-fftw-test.cpp)
target_include_directories(xtensor-fftw-test PRIVATE ${XTENSOR_FFTW_INCLUDE_DIR})
target_link_libraries(xtensor-fftw-test PRIVATE FFTW3::fftw3)
