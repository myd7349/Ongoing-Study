cmake_minimum_required(VERSION 3.14)

project(ConfigItemDemo LANGUAGES C CXX)

option(ENABLE_SIMPLEINI "Enable SimpleIni" ON)

add_definitions(-D_UNICODE)
add_definitions(-DUNICODE)

set(sources
    "main.cpp"
    "../ConfigItem.hpp"
    "../ConfigItemConverter.hpp"
    "../ConfigItemProvider.h"
    "../IniConfigItem.hpp"
    "../IniConfigItemProvider.h"
    "../IniConfigItemProvider.cpp"
    "../IPv4AddressConverter.h"
    "../IPv4AddressItem.h"
    "../StringUtility.h"
    )

if(ENABLE_SIMPLEINI)
    include(FetchContent)
    
    FetchContent_Declare(
        simpleini
        GIT_REPOSITORY https://github.com/brofield/simpleini.git
        GIT_TAG        7bca74f6535a37846162383e52071f380c99a43a
    )
    
    FetchContent_GetProperties(simpleini)
    if(NOT simpleini_POPULATED)
        FetchContent_Populate(simpleini)
        add_library(simpleini ${simpleini_SOURCE_DIR}/ConvertUTF.c)
        target_include_directories(simpleini PUBLIC ${simpleini_SOURCE_DIR})
    endif()

    list(APPEND sources
        "../SimpleIniConfigItemProvider.h"
        "../SimpleIniConfigItemProvider.cpp"
    )
endif()
    
add_executable(ConfigItemDemo ${sources})

if(ENABLE_SIMPLEINI)
    target_compile_definitions(ConfigItemDemo PRIVATE ENABLE_SIMPLEINI)
    target_link_libraries(ConfigItemDemo PRIVATE simpleini)
endif()


# References:
# https://github.com/BrightXiaoHan/CMakeTutorial
