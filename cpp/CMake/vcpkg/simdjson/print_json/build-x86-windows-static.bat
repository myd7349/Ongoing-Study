vcpkg install simdjson[exceptions,deprecated,threads]:x86-windows-static
mkdir build-x86-windows-static
cd build-x86-windows-static
cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x86-windows-static -DCMAKE_GENERATOR_PLATFORM=Win32 -DMSVC_USE_STATIC_CRT=ON
cmake --build . --config Release
Release\print_json.exe ..\CMakeSettings.json
cd ..
pause
