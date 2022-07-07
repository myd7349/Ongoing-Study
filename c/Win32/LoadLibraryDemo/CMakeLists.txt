cmake_minimum_required(VERSION 3.5)

project(LoadLibraryDemo LANGUAGES C)

add_library(foo SHARED foo.c)
target_compile_definitions(
    foo
        PUBLIC FOO_SHARED
        PRIVATE $<BUILD_INTERFACE:FOO_BUILD>
)

add_library(bar SHARED bar.c)
target_compile_definitions(
    bar
        PUBLIC BAR_SHARED
        PRIVATE $<BUILD_INTERFACE:BAR_BUILD>
)
target_link_libraries(bar PUBLIC foo)

add_executable(main main.c)
