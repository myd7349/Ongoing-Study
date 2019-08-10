vcpkg install hayai:x64-windows-static protobuf:x64-windows-static
mkdir build-x64-windows-static
cd build-x64-windows-static
cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows-static -DCMAKE_GENERATOR_PLATFORM=x64
cmake --build . --config Release
Release\bench_assign.exe
cd ..
pause
