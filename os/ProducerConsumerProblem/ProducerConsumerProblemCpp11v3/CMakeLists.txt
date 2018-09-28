cmake_minimum_required(VERSION 3.8)

project(ProducerConsumerProblemCpp11 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(ProducerConsumerProblemCpp11
    "ProducerConsumerProblemCpp11.cpp"
    "../../../cpp/Stopwatch.cpp")
