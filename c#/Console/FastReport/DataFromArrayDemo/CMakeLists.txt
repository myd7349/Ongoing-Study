cmake_minimum_required(VERSION 3.15)

project(DataFromArrayDemo LANGUAGES CSharp)

include(CSharpUtilities)

set(root_url "https://raw.githubusercontent.com/FastReports/FastReport/v2020.1.0/Demos/OpenSource/DataFromArray/DataFromArray")
set(sources)

foreach(source_file in/report.frx Program.cs Utils.cs)
    if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/sources/${source_file}")
        file(DOWNLOAD
            "${root_url}/${source_file}"
            "${CMAKE_CURRENT_BINARY_DIR}/sources/${source_file}"
        )
    endif()

    list(APPEND sources "${CMAKE_CURRENT_BINARY_DIR}/sources/${source_file}")
endforeach()

add_executable(DataFromArrayDemo ${sources})

set_property(
    TARGET DataFromArrayDemo
    PROPERTY
        DOTNET_TARGET_FRAMEWORK_VERSION "v4.0"
)
set(CMAKE_CSharp_FLAGS "/langversion:latest")

set_property(
    TARGET DataFromArrayDemo
    PROPERTY
        VS_DOTNET_REFERENCES
            "Microsoft.CSharp"
            "System"
            "System.Core"
            "System.Data"
)

set_property(
    TARGET DataFromArrayDemo
    PROPERTY
        VS_PACKAGE_REFERENCES
            "FastReport.OpenSource_2020.1.0" 
)

add_custom_command(
    TARGET DataFromArrayDemo
    POST_BUILD
    COMMAND
        "${CMAKE_COMMAND}" -E copy_if_different
        "${CMAKE_CURRENT_BINARY_DIR}/sources/in/report.frx"
        "$<TARGET_FILE_DIR:DataFromArrayDemo>/in/report.frx"
    VERBATIM
)


# References:
# https://github.com/bemehiser/cmake_csharp_example
