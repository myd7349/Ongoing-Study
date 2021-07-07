:: vcpkg install czmq[curl,draft,httpd,lz4,tool,uuid]:x64-windows-static
mkdir build-x64-windows-static
pushd build-x64-windows-static
cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows-static -DCMAKE_GENERATOR_PLATFORM=x64
cmake --build . --config Release
pushd Release
for /F %%x in ('dir /A:-D /B *.exe') do (
  set FILENAME=%%x
  echo ===========================  Run %%x ===========================
  %%x
)
popd
popd
pause
