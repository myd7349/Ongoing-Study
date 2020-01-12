cmake_minimum_required(VERSION 3.15)

project(ReportGenerator LANGUAGES CSharp)

include(CSharpUtilities)

set(sources
    Options.cs
    packages.config
    Program.cs
    Properties/AssemblyInfo.cs
)

add_executable(ReportGenerator ${sources})

csharp_set_designer_cs_properties(Properties/AssemblyInfo.cs)

set_property(
    TARGET ReportGenerator
    PROPERTY
        VS_DOTNET_REFERENCES
            "Microsoft.CSharp"
            "System"
            "System.Core"
            "System.Data"
            "System.Drawing"
)

set_property(
    TARGET ReportGenerator
    PROPERTY
        VS_PACKAGE_REFERENCES
            "CommandLineParser_2.7.82;FastReport.OpenSource_2019.3.19" 
)
