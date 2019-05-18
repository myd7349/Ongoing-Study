cmake_minimum_required(VERSION 3.8)

project(zopfli_test LANGUAGES C)

find_package(Zopfli CONFIG REQUIRED)

add_executable(zz zz.c)
if (MSVC)
    target_compile_definitions(zz PRIVATE _CRT_SECURE_NO_WARNINGS)
endif (MSVC)
target_link_libraries(zz PRIVATE Zopfli::libzopfli)
