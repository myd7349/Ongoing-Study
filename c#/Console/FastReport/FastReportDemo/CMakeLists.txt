cmake_minimum_required(VERSION 3.15)

project(FastReportDemo LANGUAGES CSharp)

include(CSharpUtilities)

set(sources
    App.config
    Movie.cs
    Program.cs
    Properties/AssemblyInfo.cs
)

add_executable(FastReportDemo ${sources})

csharp_set_designer_cs_properties(Properties/AssemblyInfo.cs)

set_property(
    TARGET FastReportDemo
    PROPERTY
        VS_DOTNET_REFERENCES
            "Microsoft.CSharp"
            "System"
            "System.Core"
            "System.Data"
)

set_property(
    TARGET FastReportDemo
    PROPERTY
        VS_PACKAGE_REFERENCES
            "FastReport.OpenSource_2020.1.0" 
)

add_custom_command(
    TARGET FastReportDemo
    POST_BUILD
    COMMAND
        "${CMAKE_COMMAND}" -E copy_if_different
        "${CMAKE_CURRENT_LIST_DIR}/report.frx"
        $<TARGET_FILE_DIR:FastReportDemo>
    VERBATIM
)

# References:
# https://stackoverflow.com/questions/18132987/cmake-and-msvs-nuget
# https://stackoverflow.com/questions/51400293/nuget-package-from-cmake
# https://github.com/bemehiser/cmake_csharp_example
