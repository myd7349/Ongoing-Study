cmake_minimum_required(VERSION 3.8)

project(filesystem-demo CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Filesystem REQUIRED COMPONENTS Experimental Final)

message(STATUS "CXX_FILESYSTEM_IS_EXPERIMENTAL: ${CXX_FILESYSTEM_IS_EXPERIMENTAL}")
message(STATUS "CXX_FILESYSTEM_HAVE_FS: ${CXX_FILESYSTEM_HAVE_FS}")
message(STATUS "CXX_FILESYSTEM_HEADER: ${CXX_FILESYSTEM_HEADER}")
message(STATUS "CXX_FILESYSTEM_NAMESPACE: ${CXX_FILESYSTEM_NAMESPACE}")

add_executable(filesystem-demo filesystem-demo.cpp)
target_compile_definitions(
    filesystem-demo
    PRIVATE
        CXX_FILESYSTEM_HEADER=<${CXX_FILESYSTEM_HEADER}>
        CXX_FILESYSTEM_NAMESPACE=${CXX_FILESYSTEM_NAMESPACE}
)
target_link_libraries(filesystem-demo PRIVATE std::filesystem)
target_compile_features(filesystem-demo PRIVATE cxx_std_17)

# References:
# https://github.com/alandefreitas/matplotplusplus/commit/a4ac853949d5b02891b18ca7c6d777b72bf6b8e8#diff-1ef7efcd62777b6d2d048781d6f097fdd5be311cab1e5252477c8288f32c77e9
# https://cmake.org/cmake/help/v3.14/manual/cmake-compile-features.7.html#requiring-language-standards
