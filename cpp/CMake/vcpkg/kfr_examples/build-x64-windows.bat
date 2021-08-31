:: https://github.com/microsoft/vcpkg/blob/master/docs/specifications/manifests.md
mkdir build-x64-windows & pushd build-x64-windows
cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows -DCMAKE_GENERATOR_PLATFORM=x64
popd
cmake --build build-x64-windows --config Release
pushd build-x64-windows\Release
for /F %%x in ('dir /A:-D /B *.exe') do (
  set FILENAME=%%x
  echo ===========================  Run %%x ===========================
  %%x
)
popd
pause
