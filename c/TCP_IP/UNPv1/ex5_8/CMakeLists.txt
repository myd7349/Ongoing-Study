cmake_minimum_required(VERSION 3.8)

project(ex5_8 LANGUAGES C)

set(root_url https://raw.githubusercontent.com/nemequ/portable-snippets/master/)

foreach (psnip_header
    builtin/builtin.h
    endian/endian.h
    exact-int/exact-int.h
    )
    file(DOWNLOAD
        ${root_url}${psnip_header}
        ${CMAKE_BINARY_DIR}/${psnip_header}
    )
endforeach ()

add_executable(ex5_8 ex5_8.c)
target_include_directories(ex5_8 PRIVATE ${CMAKE_BINARY_DIR})
