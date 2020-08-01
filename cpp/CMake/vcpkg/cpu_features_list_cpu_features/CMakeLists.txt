cmake_minimum_required(VERSION 3.9)

project(list_cpu_features C)

if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/list_cpu_features.c")
    file(DOWNLOAD
        "https://raw.githubusercontent.com/google/cpu_features/master/src/utils/list_cpu_features.c"
        "${CMAKE_CURRENT_BINARY_DIR}/list_cpu_features.c"
    )
endif()

find_package(CpuFeatures CONFIG REQUIRED)

add_executable(list_cpu_features "${CMAKE_CURRENT_BINARY_DIR}/list_cpu_features.c")
target_link_libraries(list_cpu_features PRIVATE CpuFeatures::cpu_features)
