vcpkg install septag-sx:x86-windows-static
mkdir build-x86-windows-static
cd build-x86-windows-static
cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x86-windows-static -DCMAKE_GENERATOR_PLATFORM=Win32
cmake --build . --config Release
.\Release\test-cmdline.exe -v -i a
.\Release\test-ini.exe
cd ..
pause
