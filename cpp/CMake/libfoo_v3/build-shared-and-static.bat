mkdir build-shared-and-static
cd build-shared-and-static
cmake .. -DBUILD_SHARED_LIBS=ON -DBUILD_STATIC_LIBS=ON
cmake --build . --config Release
ctest -C Release
cpack -G "NSIS;7Z"
cd ..
pause
