mkdir build-nondefault
cd build-nondefault
:: cmake .. --trace-expand
cmake .. -DCMAKE_INSTALL_PREFIX=./install
cd ..
pause
