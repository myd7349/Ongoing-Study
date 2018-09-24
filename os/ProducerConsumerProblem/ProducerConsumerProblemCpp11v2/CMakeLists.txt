cmake_minimum_required(VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

project(ProducerConsumerProblemCpp11v2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Boost 1.68.0 COMPONENTS system thread REQUIRED)

add_definitions(-DHAS_BOOST=${Boost_FOUND})

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(ProducerConsumerProblemCpp11v2
    "ProducerConsumerProblemCpp11v2.cpp"
    "../../../cpp/Stopwatch.cpp")

if(Boost_FOUND)
    target_link_libraries(ProducerConsumerProblemCpp11v2 
        ${Boost_SYSTEM_LIBRARY}
    )
endif()

# References:
# https://github.com/Microsoft/vcpkg/issues/4188
# https://stackoverflow.com/questions/1065672/how-to-link-against-boost-system-with-cmake
