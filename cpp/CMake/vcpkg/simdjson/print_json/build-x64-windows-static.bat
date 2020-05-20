vcpkg install simdjson:x64-windows-static
mkdir build-x64-windows-static
cd build-x64-windows-static
cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows-static -DCMAKE_GENERATOR_PLATFORM=x64 -DMSVC_USE_STATIC_CRT=ON
cmake --build . --config Release
Release\print_json.exe ..\CMakeSettings.json
cd ..
pause
