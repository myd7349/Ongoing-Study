vcpkg install cmocka:x64-windows-static
vcpkg install roaring:x64-windows-static
mkdir build-x64-windows-static
cd build-x64-windows-static
cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows-static -DCMAKE_GENERATOR_PLATFORM=x64 -DUSE_MSVC_STATIC_RUNTIME=ON
cmake --build . --config Release

cd src\Release
for /F %%x in ('dir /A:-D /B *.exe') do (
  set FILENAME=%%x
  echo ===========================  Run test %%x ===========================
  %%x
)

cd ..
ctest

cd ..
pause

:: References:
:: https://stackoverflow.com/questions/2591758/batch-script-loop

