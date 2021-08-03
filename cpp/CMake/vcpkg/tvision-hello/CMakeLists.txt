cmake_minimum_required(VERSION 3.8)

project(tvision-hello CXX)

find_package(tvision CONFIG REQUIRED)

set(urls
    "https://raw.githubusercontent.com/magiblot/tvision/master/hello.cpp"
)

foreach(url IN_LIST ${urls})
    get_filename_component(src_name ${url} NAME)
    if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/${src_name}")
        file(DOWNLOAD ${url} "${CMAKE_CURRENT_BINARY_DIR}/${src_name}")
    endif()
    
    get_filename_component(src_name_ne ${url} NAME_WE)
    add_executable(${src_name_ne} ${CMAKE_CURRENT_BINARY_DIR}/${src_name})
    target_link_libraries(${src_name_ne} PRIVATE tvision::tvision)
endforeach()
