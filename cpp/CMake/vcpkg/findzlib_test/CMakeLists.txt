cmake_minimum_required(VERSION 3.9)

# -- Found ZLIB: optimized;E:/vcpkg/installed/x64-windows-static/lib/zlib.lib;debug;E:/vcpkg/installed/x64-windows-static/debug/lib/zlibd.lib (found version "1.2.11")

# If I do not specify `ZLIB_ROOT` here, the output is:
# -- Found ZLIB: optimized;E:/ProgramData/Anaconda3/Library/lib/z.lib;debug;E:/vcpkg/installed/x64-windows-static/debug/lib/zlibd.lib (found version "1.2.11")

set(ZLIB_ROOT ${CMAKE_PREFIX_PATH})


find_package(ZLIB REQUIRED)

message("${CMAKE_PREFIX_PATH}")
message("${CMAKE_FIND_ROOT_PATH}")
message("${CMAKE_LIBRARY_PATH}")

