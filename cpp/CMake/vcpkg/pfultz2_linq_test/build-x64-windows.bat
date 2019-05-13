vcpkg install pfultz2-linq:x64-windows
vcpkg install boost-assign boost-foreach boost-test --triplet x64-windows
mkdir build-x64-windows
cd build-x64-windows
cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows -DCMAKE_GENERATOR_PLATFORM=x64
cmake --build . --config Release
ctest -C Release
pause
