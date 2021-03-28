cmake_minimum_required(VERSION 3.8)

project(hello-hdf5 CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(hdf5 CONFIG REQUIRED)
find_package(Filesystem REQUIRED)

add_executable(hello-hdf5 hello-hdf5.cpp)
target_link_libraries(
    hello-hdf5
    PRIVATE
        hdf5::hdf5_cpp-shared
        hdf5::hdf5_hl_cpp-shared
        std::filesystem
)
target_compile_features(hello-hdf5 PUBLIC cxx_std_17)

# References:
# https://github.com/alandefreitas/matplotplusplus/commit/a4ac853949d5b02891b18ca7c6d777b72bf6b8e8#diff-1ef7efcd62777b6d2d048781d6f097fdd5be311cab1e5252477c8288f32c77e9
# https://cmake.org/cmake/help/v3.14/manual/cmake-compile-features.7.html#requiring-language-standards
