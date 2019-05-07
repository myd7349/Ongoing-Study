cmake_minimum_required(VERSION 3.2)

project(rdkafka-examples C CXX)

find_package(RdKafka CONFIG REQUIRED)

if(WIN32)
    set(win32_sources wingetopt.c wingetopt.h)
endif(WIN32)

add_executable(rdkafka_simple_producer rdkafka_simple_producer.c ${win32_sources})
target_link_libraries(rdkafka_simple_producer PUBLIC RdKafka::rdkafka)

add_executable(rdkafka_performance rdkafka_performance.c ${win32_sources})
target_include_directories(rdkafka_performance PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rdkafka_performance PUBLIC RdKafka::rdkafka)

add_executable(rdkafka_example_cpp rdkafka_example.cpp ${win32_sources})
target_link_libraries(rdkafka_example_cpp PUBLIC RdKafka::rdkafka++)

add_executable(rdkafka_consumer_example_cpp rdkafka_consumer_example.cpp ${win32_sources})
target_link_libraries(rdkafka_consumer_example_cpp PUBLIC RdKafka::rdkafka++)

# The targets below has Unix include dirs and do not compile on Windows.
if(NOT WIN32)
    add_executable(rdkafka_example rdkafka_example.c)
    target_link_libraries(rdkafka_example PUBLIC RdKafka::rdkafka)
    
    add_executable(rdkafka_consumer_example rdkafka_consumer_example.c)
    target_link_libraries(rdkafka_consumer_example PUBLIC RdKafka::rdkafka)
    
    add_executable(kafkatest_verifiable_client kafkatest_verifiable_client.cpp)
    target_link_libraries(kafkatest_verifiable_client PUBLIC RdKafka::rdkafka++)
endif(NOT WIN32)
