cmake_minimum_required(VERSION 3.9)

# In fact, we can use:
# project(FilterAPITest LANGUAGES CSharp)
# here.
# But that will give you an unset CMAKE_SIZEOF_VOID_P.
project(FilterAPITest LANGUAGES CSharp C)

include(CSharpUtilities)

set(sources
    App.config
    Program.cs
    Properties/AssemblyInfo.cs
)

add_executable(FilterAPITest ${sources})

target_link_libraries(FilterAPITest PRIVATE FilterManaged)

csharp_set_designer_cs_properties(Properties/AssemblyInfo.cs)

#set_property(TARGET FilterAPITest PROPERTY DOTNET_TARGET_FRAMEWORK_VERSION "v4.6.1")
#set(CMAKE_CSharp_FLAGS "/langversion:6")

set_property(
    TARGET FilterAPITest
    PROPERTY VS_DOTNET_REFERENCES
        "Microsoft.CSharp"
        "System"
        "System.Core"
)

message(STATUS "CMAKE_SIZEOF_VOID_P: ${CMAKE_SIZEOF_VOID_P}")

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    target_compile_options(FilterAPITest PRIVATE "/platform:anycpu")
else ()
    target_compile_options(FilterAPITest PRIVATE "/platform:x86")
endif ()

add_custom_command(
    TARGET FilterAPITest
    POST_BUILD
    COMMAND
        "${CMAKE_COMMAND}" -E copy_if_different
        $<TARGET_FILE:FilterNative>
        $<TARGET_FILE_DIR:FilterAPITest>
    VERBATIM
)

# References:
# [Generate C# project using CMake](https://stackoverflow.com/questions/2074144/generate-c-sharp-project-using-cmake)
# [add_library is not working in CMake for adding CSharp source files?](https://stackoverflow.com/questions/18888266/add-library-is-not-working-in-cmake-for-adding-csharp-source-files)
# [What is the purpose of the “Prefer 32-bit” setting in Visual Studio and how does it actually work?](https://stackoverflow.com/questions/12066638/what-is-the-purpose-of-the-prefer-32-bit-setting-in-visual-studio-and-how-does)
# [CMake - Building C# without Prefer 32-bit Flag](https://stackoverflow.com/questions/50614863/cmake-building-c-sharp-without-prefer-32-bit-flag)
# [CMake on a C# project: Any CPU?](https://stackoverflow.com/questions/58591485/cmake-on-a-c-sharp-project-any-cpu)
# https://github.com/bemehiser/cmake_csharp_example
