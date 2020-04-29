vcpkg install getopt:x64-windows
mkdir build-with-vcpkg
cd build-with-vcpkg
cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows -DCMAKE_GENERATOR_PLATFORM=x64
cmake --build . --config Release
cd ..
pause

:: -- Looking for getopt_long
:: -- Looking for getopt_long - not found
:: -- Looking for getopt_long
:: -- Looking for getopt_long - found
:: -- GETOPT_INCLUDE_DIR: E:/vcpkg/installed/x64-windows/include
:: -- GETOPT_LIBRARY: E:/vcpkg/installed/x64-windows/debug/lib/getopt.lib
:: -- HAVE_GETOPT_LONG_FUNC:
:: -- HAVE_GETOPT_LONG_SYM:
