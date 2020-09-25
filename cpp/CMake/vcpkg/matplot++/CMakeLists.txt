cmake_minimum_required(VERSION 3.8)

project(matplotplusplus-test CXX)

find_package(Matplot++ CONFIG REQUIRED)

set(urls
    "https://raw.githubusercontent.com/alandefreitas/matplotplusplus/v1.0.1/examples/line_plot/plot/plot_1.cpp"
    "https://raw.githubusercontent.com/alandefreitas/matplotplusplus/v1.0.1/test/backends/ogl_main.cpp"
)

foreach(url ${urls})
    get_filename_component(src_name ${url} NAME)
    if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/${src_name}")
        file(DOWNLOAD ${url} "${CMAKE_CURRENT_BINARY_DIR}/${src_name}")
    endif()
    
    get_filename_component(src_name_ne ${url} NAME_WE)
    add_executable(${src_name_ne} ${CMAKE_CURRENT_BINARY_DIR}/${src_name})
    target_link_libraries(${src_name_ne} PRIVATE Matplot++::matplot)
endforeach()
