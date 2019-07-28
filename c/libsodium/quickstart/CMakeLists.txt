cmake_minimum_required(VERSION 3.8)

project(libsodium-quickstart C)

find_package(unofficial-sodium CONFIG REQUIRED)

foreach (src
    boilerplate.c
    randombytes.c
    hashing.c
    pwhash.c
)
    get_filename_component(src_name ${src} NAME_WE)
    add_executable(${src_name} ${src})
    target_link_libraries(${src_name} PRIVATE unofficial-sodium::sodium)
endforeach ()
