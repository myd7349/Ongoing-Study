cmake_minimum_required(VERSION 3.8)

project(test_compile_definition C)

add_executable(style1 main.c)
target_compile_definitions(style1 PRIVATE HAVE_SSL HAVE_ZLIB)

add_executable(style2 main.c)
target_compile_definitions(style2 PRIVATE HAVE_SSL=1 HAVE_ZLIB=1)

add_executable(style3 main.c)
target_compile_definitions(style3 PRIVATE HAVE_SSL=0 HAVE_ZLIB=0)

# References:
# https://github.com/edenhill/librdkafka/pull/2323
