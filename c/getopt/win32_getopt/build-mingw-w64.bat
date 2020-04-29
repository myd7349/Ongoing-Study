mkdir build-mingw-w64
cd build-mingw-w64
cmake .. -G "MinGW Makefiles"
cmake --build . --config Release
cd ..
pause

:: -- Looking for getopt_long
:: -- Looking for getopt_long - found
:: -- Looking for getopt_long
:: -- Looking for getopt_long - found
:: -- GETOPT_INCLUDE_DIR: GETOPT_INCLUDE_DIR-NOTFOUND
:: -- GETOPT_LIBRARY: GETOPT_LIBRARY-NOTFOUND
:: -- HAVE_GETOPT_LONG_FUNC: 1
:: -- HAVE_GETOPT_LONG_SYM: 1
