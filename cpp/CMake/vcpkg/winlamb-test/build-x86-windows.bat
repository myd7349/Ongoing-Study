mkdir build-x86-windows & pushd build-x86-windows
cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x86-windows -DCMAKE_GENERATOR_PLATFORM=Win32
popd
cmake --build build-x86-windows --config Release
pushd build-x86-windows\Release
for /F %%x in ('dir /A:-D /B *.exe') do (
  set FILENAME=%%x
  echo ===========================  Run %%x ===========================
  %%x
)
popd
pause
