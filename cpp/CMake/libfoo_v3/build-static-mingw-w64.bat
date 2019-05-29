mkdir build-static-mingw-w64
cd build-static-mingw-w64
cmake .. -G "MinGW Makefiles" -DBUILD_SHARED_LIBS=OFF -DBUILD_STATIC_LIBS=ON
cmake --build . --config Release
ctest -C Release
cpack -G "NSIS;7Z"
cd ..
pause
