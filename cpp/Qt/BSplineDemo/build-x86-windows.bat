vcpkg install qt5-base tinyspline
mkdir build-x86-windows
cd build-x86-windows
cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x86-windows -DCMAKE_GENERATOR_PLATFORM=Win32 -DUSE_EXTERNAL_TINYSPLINE=ON
cmake --build . --config Debug
cd ..
pause
