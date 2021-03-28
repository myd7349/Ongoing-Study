cmake_minimum_required(VERSION 3.8)

project(attribute-demo LANGUAGES CXX)

find_package(hdf5 CONFIG REQUIRED)

add_executable(attribute-demo attribute-demo.cpp)
target_link_libraries(attribute-demo PRIVATE hdf5::hdf5_cpp-shared)
target_compile_features(attribute-demo PRIVATE cxx_std_11)


# References:
# [How do I activate C++ 11 in CMake?](https://stackoverflow.com/questions/10851247/how-do-i-activate-c-11-in-cmake)
# [Take control of your vcpkg dependencies with versioning support](https://devblogs.microsoft.com/cppblog/take-control-of-your-vcpkg-dependencies-with-versioning-support/)
