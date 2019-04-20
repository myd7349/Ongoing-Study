cmake_minimum_required(VERSION 3.8)

project(librdkafka_pr_2274 CXX)

find_package(RdKafka CONFIG REQUIRED)

add_executable(librdkafka_pr_2274 librdkafka_pr_2274.cpp)
target_link_libraries(librdkafka_pr_2274 PRIVATE RdKafka::rdkafka++)

# References:
# https://github.com/edenhill/librdkafka/pull/2274
