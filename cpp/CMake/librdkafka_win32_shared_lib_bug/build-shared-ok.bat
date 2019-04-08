mkdir build-shared-ok
cd build-shared-ok
cmake .. -DBUILD_SHARED_LIBS=ON -DREPRODUCE_WIN32_SHARED_LIBS_BUG=OFF
cmake --build . --config Release
ctest . -C Release
tests\Release\rd_export_test.exe
pause
