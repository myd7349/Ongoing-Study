mkdir build-mingw-w64-ok
cd build-mingw-w64-ok
cmake .. -G "MinGW Makefiles" -DSHARED=ON -DSTATIC=OFF -DBUILD_EXAMPLES=ON -DREPRODUCE_CI_BUILD_ERROR=OFF
cmake --build . --config Release
cd ..
pause
