vcpkg install tinyply:x86-windows
mkdir build-x86-windows-old
cd build-x86-windows-old
cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x86-windows -DCMAKE_GENERATOR_PLATFORM=Win32 -DUSE_CMAKE_TARGET=OFF
cmake --build . --config Release
Release\tinyply_example.exe
pause
