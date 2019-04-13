mkdir build-shared
cd build-shared
cmake .. -DBUILD_SHARED_LIBS=ON -DBUILD_STATIC_LIBS=OFF
cmake --build . --config Release
ctest . -C Release
cd ..
pause
