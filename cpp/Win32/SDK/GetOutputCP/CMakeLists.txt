cmake_minimum_required(VERSION 3.14)
project(GetOutputCP CXX)

add_executable(GetOutputCP-GBK GetOutputCP-GBK.cpp)

add_executable(GetOutputCP-UTF8-v1 GetOutputCP-UTF8.cpp)
target_compile_options(GetOutputCP-UTF8-v1 PRIVATE /source-charset:utf-8)

add_executable(GetOutputCP-UTF8-v1-SetCP GetOutputCP-UTF8.cpp)
target_compile_definitions(GetOutputCP-UTF8-v1-SetCP PRIVATE SET_CP_UTF8)
target_compile_options(GetOutputCP-UTF8-v1-SetCP PRIVATE /source-charset:utf-8)

add_executable(GetOutputCP-UTF8-v2 GetOutputCP-UTF8.cpp UTF-8.manifest)
target_compile_options(GetOutputCP-UTF8-v2 PRIVATE /utf-8)

add_executable(GetOutputCP-UTF8-v2-SetCP GetOutputCP-UTF8.cpp UTF-8.manifest)
target_compile_definitions(GetOutputCP-UTF8-v2-SetCP PRIVATE SET_CP_UTF8)
target_compile_options(GetOutputCP-UTF8-v2-SetCP PRIVATE /utf-8)

# References:
# [How can I embed a specific manifest file in a Windows DLL with a CMake build?](https://stackoverflow.com/questions/6335352/how-can-i-embed-a-specific-manifest-file-in-a-windows-dll-with-a-cmake-build)
