vcpkg install cmocka:x64-windows
vcpkg install roaring:x64-windows
mkdir build-x64-windows
cd build-x64-windows
cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows -DCMAKE_GENERATOR_PLATFORM=x64
cmake --build . --config Release

cd src\Release
for /F %%x in ('dir /A:-D /B *.exe') do (
  set FILENAME=%%x
  echo ===========================  Run test %%x ===========================
  %%x
)

cd ..\..\
pause

:: References:
:: https://stackoverflow.com/questions/2591758/batch-script-loop

