vcpkg install benchmark:x86-windows
mkdir build-x86-windows & pushd build-x86-windows
cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x86-windows -DCMAKE_GENERATOR_PLATFORM=Win32
popd
cmake --build build-x86-windows --config Release
build-x86-windows\Release\shift_array_elements.exe
pause
