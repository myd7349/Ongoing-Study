mkdir build-static
cd build-static
cmake ..
cmake --build . --config Release
ctest . -C Release
pause
