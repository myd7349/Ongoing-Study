:: https://github.com/microsoft/vcpkg/blob/master/docs/specifications/manifests.md
mkdir build-x64-windows-static & pushd build-x64-windows-static
cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows-static -DCMAKE_GENERATOR_PLATFORM=x64 -DMSVC_STATIC_RUNTIME=ON
popd
cmake --build build-x64-windows-static --config Release
build-x64-windows-static\Release\attribute-demo.exe
pause
