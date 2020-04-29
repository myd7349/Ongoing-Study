mkdir build-mingw-w64
cd build-mingw-w64
:: cmake .. --trace-expand
cmake .. -G "MinGW Makefiles"
cd ..
pause