# CMakeList.txt : CMake project for vcpkg_cmake_toolchain_demo, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# TODO: Add tests and install targets if needed.
find_package(sqlite3 REQUIRED)

link_libraries(sqlite3)

# Add source to this project's executable.
add_executable (main "main.cpp")
