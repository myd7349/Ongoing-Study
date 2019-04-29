vcpkg install taocpp-json:x86-windows-static
mkdir build-x86-windows-static
cd build-x86-windows-static
cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x86-windows-static -DCMAKE_GENERATOR_PLATFORM=Win32 -DUSE_STATIC_RTL=ON
cmake --build . --config Release
cd ..
pause
