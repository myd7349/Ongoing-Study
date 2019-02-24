mkdir build-x64-windows
cd build-x64-windows
cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows -DCMAKE_GENERATOR_PLATFORM=x64 -DUSE_STATIC_RTL=OFF
cmake --build . --config Release
Release\onig_count
cd ..
pause
