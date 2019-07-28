cmake_minimum_required(VERSION 3.8)

project(libhydrogen-examples C)

find_package(hydrogen CONFIG REQUIRED)

foreach (src init.c rand.c)
    get_filename_component(src_name ${src} NAME_WE)
    add_executable(${src_name} ${src})
    target_link_libraries(${src_name} PRIVATE hydrogen::hydrogen)
endforeach ()
