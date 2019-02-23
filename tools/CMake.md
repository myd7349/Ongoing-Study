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
