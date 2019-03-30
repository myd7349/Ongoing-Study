vcpkg install cmocka:x86-windows-static
vcpkg install roaring:x86-windows-static
mkdir build-x86-windows-static
cd build-x86-windows-static
cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x86-windows-static -DCMAKE_GENERATOR_PLATFORM=Win32 -DUSE_MSVC_STATIC_RUNTIME=ON
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

