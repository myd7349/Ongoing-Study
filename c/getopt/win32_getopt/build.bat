mkdir build
cd build
cmake .. -G "Visual Studio 16 2019" -A x64
cmake --build . --config Release
cd ..
pause

:: -- Looking for getopt_long
:: -- Looking for getopt_long - not found
:: -- Looking for getopt_long
:: -- Looking for getopt_long - not found
:: -- GETOPT_INCLUDE_DIR: GETOPT_INCLUDE_DIR-NOTFOUND
:: -- GETOPT_LIBRARY: GETOPT_LIBRARY-NOTFOUND
:: -- HAVE_GETOPT_LONG_FUNC:
:: -- HAVE_GETOPT_LONG_SYM:

:: If we have already installed `getopt-win32:x64-windows` through `vcpkg`
:: and vcpkg's integration with Visual Studio 2019 is OK, then we may saw:

:: -- Looking for getopt_long
:: -- Looking for getopt_long - not found
:: -- Looking for getopt_long
:: -- Looking for getopt_long - found
:: -- GETOPT_INCLUDE_DIR: GETOPT_INCLUDE_DIR-NOTFOUND
:: -- GETOPT_LIBRARY: GETOPT_LIBRARY-NOTFOUND
:: -- HAVE_GETOPT_LONG_FUNC:
:: -- HAVE_GETOPT_LONG_SYM: 1
