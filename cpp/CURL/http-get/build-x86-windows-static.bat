:: https://github.com/microsoft/vcpkg/blob/master/docs/specifications/manifests.md
mkdir build-x86-windows-static & pushd build-x86-windows-static
cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x86-windows-static -DCMAKE_GENERATOR_PLATFORM=Win32
popd
cmake --build build-x86-windows-static --config Release
pushd build-x86-windows-static\Release
for /F %%x in ('dir /A:-D /B *.exe') do (
  set FILENAME=%%x
  echo ===========================  Run %%x ===========================
  %%x
)
popd
pause
