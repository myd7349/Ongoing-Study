mkdir build-mingw-w64-fail
cd build-mingw-w64-fail
cmake .. -G "MinGW Makefiles" -DSHARED=ON -DSTATIC=OFF -DBUILD_EXAMPLES=ON -DREPRODUCE_CI_BUILD_ERROR=ON
cmake --build . --config Release
cd ..
pause
