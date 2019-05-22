mkdir build
cd build
cmake .. -DVCPKG_TARGET_TRIPLET=x86-windows -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake"
pause
