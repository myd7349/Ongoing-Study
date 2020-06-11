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
