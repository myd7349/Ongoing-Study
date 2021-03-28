cmake_minimum_required(VERSION 3.8)

project(byte-order-demo LANGUAGES CXX)

find_package(hdf5 CONFIG REQUIRED)
find_package(unofficial-portable-snippets CONFIG REQUIRED)

add_executable(byte-order-demo byte-order-demo.cpp)
target_include_directories(
    byte-order-demo
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/../../Google/protobuf/new_data_format")
target_link_libraries(byte-order-demo PRIVATE hdf5::hdf5_cpp-shared unofficial::portable-snippets::endian)
target_compile_features(byte-order-demo PRIVATE cxx_std_11)


# References:
# [How do I activate C++ 11 in CMake?](https://stackoverflow.com/questions/10851247/how-do-i-activate-c-11-in-cmake)
# [Take control of your vcpkg dependencies with versioning support](https://devblogs.microsoft.com/cppblog/take-control-of-your-vcpkg-dependencies-with-versioning-support/)
