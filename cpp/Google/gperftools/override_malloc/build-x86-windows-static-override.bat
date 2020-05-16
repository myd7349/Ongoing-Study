vcpkg install gperftools[override]:x86-windows-static
mkdir build-x86-windows-static-override
cd build-x86-windows-static-override
cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x86-windows-static -DCMAKE_GENERATOR_PLATFORM=Win32 -DGPERFTOOLS_WIN32_OVERRIDE_ALLOCATORS=ON
cmake --build . --config Release
Release\override_malloc.exe
cd ..
pause
