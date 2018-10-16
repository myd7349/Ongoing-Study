cmake_minimum_required(VERSION 3.8)

project(ConfigItemDemo LANGUAGES CXX)

add_definitions(-D_UNICODE)
add_definitions(-DUNICODE)

add_executable(ConfigItemDemo
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
