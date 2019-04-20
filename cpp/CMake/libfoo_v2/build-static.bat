mkdir build-static
cd build-static
cmake .. -DBUILD_SHARED_LIBS=OFF -DBUILD_STATIC_LIBS=ON
cmake --build . --config Release
ctest . -C Release
cpack -G "NSIS;7Z"
cd ..
pause
