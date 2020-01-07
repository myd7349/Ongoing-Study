cmake_minimum_required(VERSION 3.9)

# In fact, we can use:
# project(FilterAPITest LANGUAGES CSharp)
# here.
# But that will give you an unset CMAKE_SIZEOF_VOID_P.
project(FilterManaged LANGUAGES CSharp C)

include(CSharpUtilities)

set(sources
    Filter.cs
    FilterType.cs
    Properties/AssemblyInfo.cs
)

add_library(FilterManaged SHARED ${sources})

csharp_set_designer_cs_properties(Properties/AssemblyInfo.cs)

#set_property(TARGET FilterManaged PROPERTY DOTNET_TARGET_FRAMEWORK_VERSION "v4.6.1")
#set(CMAKE_CSharp_FLAGS "/langversion:6")

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    target_compile_options(FilterManaged PRIVATE "/platform:anycpu")
else ()
    target_compile_options(FilterManaged PRIVATE "/platform:x86")
endif ()

set_property(
    TARGET FilterManaged
    PROPERTY VS_DOTNET_REFERENCES
        "Microsoft.CSharp"
        "System"
        "System.Core"
)

# References:
# [Generate C# project using CMake](https://stackoverflow.com/questions/2074144/generate-c-sharp-project-using-cmake)
# [add_library is not working in CMake for adding CSharp source files?](https://stackoverflow.com/questions/18888266/add-library-is-not-working-in-cmake-for-adding-csharp-source-files)
# [CMake - Building C# without Prefer 32-bit Flag](https://stackoverflow.com/questions/50614863/cmake-building-c-sharp-without-prefer-32-bit-flag)
# [CMake on a C# project: Any CPU?](https://stackoverflow.com/questions/58591485/cmake-on-a-c-sharp-project-any-cpu)
# https://github.com/bemehiser/cmake_csharp_example
