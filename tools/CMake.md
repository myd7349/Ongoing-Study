https://github.com/CLIUtils/modern_cmake

[CMake and the Future of C++ Package Management](https://ibob.bg/blog/2020/01/13/cmake-package-management/)

https://github.com/cpm-cmake/CPM.cmake

1. cmake -G "Visual Studio 10 2010" ..

2. E:\vcpkg>vcpkg.exe integrate install
    >Applied user-wide integration for this vcpkg root.
    >
    >All MSBuild C++ projects can now #include any installed libraries.
    >Linking will be handled automatically.
    >Installing new libraries will make them instantly available.
    >
    >CMake projects should use: "-DCMAKE_TOOLCHAIN_FILE=e:/vcpkg/scripts/buildsystems/vcpkg.cmake"

3. Specify toolchain file

    - [CMake: specifying build toolchain](https://stackoverflow.com/questions/5098360/cmake-specifying-build-toolchain)
    - [CMAKE_TOOLCHAIN_FILE only recognized on command line](https://github.com/queezythegreat/arduino-cmake/issues/38)
    - [cmake : Set environment variables from a script](https://stackoverflow.com/questions/21047399/cmake-set-environment-variables-from-a-script)
    - [Cross Compiling](https://gitlab.kitware.com/cmake/community/wikis/doc/cmake/CrossCompiling)

4. Specify build type

    - [CMAKE_BUILD_TYPE not being used in CMakeLists.txt](https://stackoverflow.com/questions/24460486/cmake-build-type-not-being-used-in-cmakelists-txt)

5. [Difference between CMAKE_CURRENT_SOURCE_DIR and CMAKE_CURRENT_LIST_DIR](https://stackoverflow.com/questions/24460486/cmake-build-type-not-being-used-in-cmakelists-txt)

6. [OS specific instructions in CMAKE: How to?](https://stackoverflow.com/questions/9160335/os-specific-instructions-in-cmake-how-to)

7. Couldn't find Threads when building raylib on Ubuntu:
* [cmake and libpthread](https://stackoverflow.com/questions/1620918/cmake-and-libpthread)
* [How to get CMake to recognize pthread on Ubuntu?](https://stackoverflow.com/questions/15193785/how-to-get-cmake-to-recognize-pthread-on-ubuntu)
* [CMake can't find pthread](https://askubuntu.com/questions/499238/cmake-cant-find-pthread)
* [CMake failing to detect pthreads due to warnings](https://stackoverflow.com/questions/24813827/cmake-failing-to-detect-pthreads-due-to-warnings/25130590#25130590)

8. Couldn't find OpenGL on Linux
* [How to use CMake to find and link OpenGL(mesa) package in Ubuntu](https://stackoverflow.com/questions/34001996/how-to-use-cmake-to-find-and-link-openglmesa-package-in-ubuntu)
* [Couldn't find OpenGL on Ubuntu](https://stackoverflow.com/questions/31170869/cmake-could-not-find-opengl-in-ubuntu)

9. Setting the MSVC runtime in CMake
* [Setting the MSVC runtime in CMake](https://stackoverflow.com/questions/10113017/setting-the-msvc-runtime-in-cmake)

10. [When should I quote variables?](https://stackoverflow.com/questions/35847655/when-should-i-quote-variables)

11. [CMake FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html)
* [imgui-plot](https://github.com/soulthreads/imgui-plot)

12. Override options in subdirectory
* [Override options in cmake subproject](https://stackoverflow.com/questions/14061605/override-option-in-cmake-subproject)
* [CMake: set subdirectory options](https://stackoverflow.com/questions/20239334/cmake-set-subdirectory-options)

13. MSVC UTF-8
* [Possible to force CMake/MSVC to use UTF-8 encoding for source files without a BOM? C4819](https://stackoverflow.com/questions/47690822/possible-to-force-cmake-msvc-to-use-utf-8-encoding-for-source-files-without-a-bo)
* https://github.com/ethereum/aleth/issues/4102

14. Threads
* [cmake and libpthread](https://stackoverflow.com/questions/1620918/cmake-and-libpthread)
* [Significance of -pthread flag when compiling](https://stackoverflow.com/questions/2127797/significance-of-pthread-flag-when-compiling)

15. CMAKE_BUILD_TYPE
* [CMAKE_BUILD_TYPE is not being used in CMakeLists.txt](https://stackoverflow.com/questions/24460486/cmake-build-type-is-not-being-used-in-cmakelists-txt)

16. CMAKE_CXX_COMPILER_ID
* [In CMake, how can I test if the compiler is Clang?](https://stackoverflow.com/questions/10046114/in-cmake-how-can-i-test-if-the-compiler-is-clang)

17. C++17
* [How to enable C++17 in CMake](https://stackoverflow.com/questions/45688522/how-to-enable-c17-in-cmake)
> target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)

18.
* [CMAKE_RUNTIME_OUTPUT_DIRECTORY](https://github.com/microsoft/vcpkg/issues/11547#issuecomment-633211556)

19. libm
* [Can CMake detect if I need to link to libm when using pow in C?](https://stackoverflow.com/questions/32816646/can-cmake-detect-if-i-need-to-link-to-libm-when-using-pow-in-c)

20.
* [CMake install](https://github.com/uriparser/uriparser/pull/75)

21
* [CMAKE_CURRENT_SOURCE_DIR vs PROJECT_SOURCE_DIR](https://github.com/mandreyel/mio/commit/61567f4c579aeb2ec1ab8f6bc285de461c7149a8)

22.
* https://github.com/llvm/llvm-project/commit/bb73d1b278eb478ca8e56153cf1469bf7eb13a3f
> include_directories(AFTER ${CMAKE_CURRENT_BINARY_DIR})

https://github.com/rafat/wavelib/blob/a92456d2e20451772dd76c2a0a3368537ee94184/CMakeLists.txt#L24-L25
```cmake
# cleanup prefix lib for Unix-like OSes
set(CMAKE_SHARED_MODULE_PREFIX)
```

[CMake and Boost](https://github.com/microsoft/vcpkg/issues/4188)
```cmake
cmake_minimum_required (VERSION 3.10)

project ("Example" LANGUAGES CXX)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS random )# asio is header only no library, random is for example
include_directories(${Boost_INCLUDE_DIR})

add_executable (Example "Example.cpp")
target_link_libraries(Example ${Boost_LIBRARIES})
```

[How to detect if 64 bit MSVC with cmake?](https://stackoverflow.com/questions/39258250/how-to-detect-if-64-bit-msvc-with-cmake)
```cmake
if(NOT "${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)")
    ...
endif()

if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
    ...
endif()

if(NOT CMAKE_CL_64)
   ...
endif()
```

> [Beware of the cmake 3.14 release, now the bitness in the generator name is dropped.](https://cmake.org/cmake/help/v3.14/generator/Visual%20Studio%2016%202019.html#generator:Visual%20Studio%2016%202019)

```bash
cmake -G "Visual Studio 16 2019" -A Win32
cmake -G "Visual Studio 16 2019" -A x64
cmake -G "Visual Studio 16 2019" -A ARM
cmake -G "Visual Studio 16 2019" -A ARM64
```

[How can I install a hierarchy of files using CMake?](https://stackoverflow.com/questions/11096471/how-can-i-install-a-hierarchy-of-files-using-cmake)

[cmake glob include while preserving directory structure](https://stackoverflow.com/questions/6216554/cmake-glob-include-while-preserving-directory-structure)

https://github.com/google/benchmark/blob/master/cmake/AddCXXCompilerFlag.cmake

[CMake & Ninja](https://twitter.com/lichray/status/1358689765684617216)
> cmake -G "Ninja Multi-Config" -B build



[set_source_files_properties](https://github.com/google/marl/commit/e82d1a7b8bca94cca68e0000e866289e2cf29ccc)

>set_source_files_properties(
>
>​    ......
>
>​    PROPERTIES LANGUAGE C
>
>)

[future-proof CMake](https://github.com/kimwalisch/libpopcnt/commit/870e63dba35050c60a45f3b63f2d0138154eeaf9)

> cmake_minimum_required(VERSION 3.4...3.19)

[cmkr](https://github.com/MoAlyousef/cmkr)

[cmakepp](https://github.com/toeb/cmakepp)

[How to build x86 and/or x64 on Windows from command line with CMAKE?](https://stackoverflow.com/questions/28350214/how-to-build-x86-and-or-x64-on-windows-from-command-line-with-cmake)

23. [Is there a CMake '--install' switch?](https://stackoverflow.com/questions/34040522/is-there-a-cmake-install-switch)

24. [cmake set subdirectory options](https://stackoverflow.com/questions/20239334/cmake-set-subdirectory-options/20239564)

25. https://github.com/Neumann-A/CMakeJSON

26. [CMake Presets integration in Visual Studio and Visual Studio Code](https://devblogs.microsoft.com/cppblog/cmake-presets-integration-in-visual-studio-and-visual-studio-code/)

27. https://github.com/ess-dmsc/h5cpp/blob/master/cmake/cmake_uninstall.cmake.in

28. https://github.com/KhronosGroup/glslang/blob/master/parse_version.cmake

    https://github.com/KhronosGroup/glslang/blob/9431c53c84c14fa9e9cd37678262ebba55c62c87/parse_version.cmake#L23-L41
    
29. [WIN32 var has been deprecated in later versions of cmake.](https://github.com/google/glog/commit/d2fed749a5a69354b22c32ee128f5dbabeeabcf3)

30. https://github.com/hosseinmoein/DataFrame/blob/master/cmake/AddUninstallTarget.cmake

31. [CMake compare to empty string with STREQUAL failed](https://stackoverflow.com/questions/19982340/cmake-compare-to-empty-string-with-strequal-failed)

32. [Define DEBUG and RELEASE symbols in Visual Studio Code](https://stackoverflow.com/questions/58783805/define-debug-and-release-symbols-in-visual-studio-code)

33. VS Code and CMake

    - [Configure Visual Studio Code for CMake with some options](https://stackoverflow.com/questions/42423536/configure-visual-studio-code-for-cmake-with-some-options)
    - [Getting Started](https://vector-of-bool.github.io/docs/vscode-cmake-tools/getting_started.html#getting-started)
    - [Configuring CMake Tools](https://vector-of-bool.github.io/docs/vscode-cmake-tools/settings.html#conf-cmake-configuresettings)
    - [CMake Configuring](https://vector-of-bool.github.io/docs/vscode-cmake-tools/configuring.html#configuring)
    
34. CMake project templates

    - https://github.com/friendlyanon/cmake-init
    - https://github.com/friendlyanon/cxx-static-shared-example
    - https://github.com/friendlyanon/cmake-init-executable
    - https://github.com/friendlyanon/cmake-init-header-only
    
35. FindPackageHandleStandardArgs.cmake

    > `REQUIRED_VARS` specify the variables which are required for this package.
    >
    > These may be named in the generated failure message asking the user to set the missing variable values. Therefore these should typically be cache entries such as `FOO_LIBRARY` and not output variables like `FOO_LIBRARIES`.
    
    [What does FindPackageHandleStandardArgs do exactly?](https://stackoverflow.com/questions/52785157/what-does-findpackagehandlestandardargs-do-exactly)
    
    Good:
    
    > ```cmake
    > # https://github.com/facebook/folly/blob/427077374736415f4eb6c497f9172ae9e4a9f1d7/CMake/FindFmt.cmake#L15-L41
    > find_path(LIBFMT_INCLUDE_DIR fmt/core.h)
    > mark_as_advanced(LIBFMT_INCLUDE_DIR)
    > 
    > find_library(LIBFMT_LIBRARY NAMES fmt fmtd)
    > mark_as_advanced(LIBFMT_LIBRARY)
    > 
    > include(FindPackageHandleStandardArgs)
    > FIND_PACKAGE_HANDLE_STANDARD_ARGS(
    >     LIBFMT
    >     DEFAULT_MSG
    >     LIBFMT_LIBRARY LIBFMT_INCLUDE_DIR)
    > 
    > if(LIBFMT_FOUND)
    >     set(LIBFMT_LIBRARIES ${LIBFMT_LIBRARY})
    >     set(LIBFMT_INCLUDE_DIRS ${LIBFMT_INCLUDE_DIR})
    >     message(STATUS "Found {fmt}: ${LIBFMT_LIBRARY}")
    >     add_library(fmt::fmt UNKNOWN IMPORTED)
    >     set_target_properties(
    >       fmt::fmt PROPERTIES
    >       INTERFACE_INCLUDE_DIRECTORIES "${LIBFMT_INCLUDE_DIR}"
    >     )
    >     set_target_properties(
    >       fmt::fmt PROPERTIES
    >       IMPORTED_LINK_INTERFACE_LANGUAGES "C"
    >       IMPORTED_LOCATION "${LIBFMT_LIBRARY}"
    >     )
    > endif()
    > ```
    
    Good:
    
    FindCURL.cmake
    
    Bad:
    
    https://github.com/zeromq/czmq/blob/master/Findlibzmq.cmake
    
36. https://github.com/desktop-app/cmake_helpers

37. cmake_push_check_state

    https://github.com/google/glog/pull/724/files

