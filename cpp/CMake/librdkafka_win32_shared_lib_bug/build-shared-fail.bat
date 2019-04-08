mkdir build-shared-fail
cd build-shared-fail
cmake .. -DBUILD_SHARED_LIBS=ON
cmake --build . --config Release
ctest . -C Release
tests\Release\rd_export_test.exe
pause
