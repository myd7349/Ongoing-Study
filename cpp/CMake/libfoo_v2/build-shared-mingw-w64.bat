mkdir build-shared-mingw-w64
cd build-shared-mingw-w64
cmake .. -G "MinGW Makefiles" -DBUILD_SHARED_LIBS=ON -DBUILD_STATIC_LIBS=OFF
cmake --build . --config Release
ctest . -C Release
cpack -G "NSIS;7Z"
cd ..
pause
