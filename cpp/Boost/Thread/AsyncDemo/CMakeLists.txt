cmake_minimum_required(VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

project(AsyncDemo LANGUAGES CXX)

find_package(Boost 1.68.0 COMPONENTS system thread REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(AsyncDemo "AsyncDemo.cpp")

target_link_libraries(AsyncDemo
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    )

# References:
# Ongoing-Study/os/ProducerConsumerProblem/ProducerConsumerProblemCpp11v2/CMakeLists.txt
