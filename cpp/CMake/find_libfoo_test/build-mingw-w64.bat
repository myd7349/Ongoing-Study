call "%~dp0\install_libfoo-mingw-w64.bat"
cd /d "%~dp0"
cd build
cmake .. -G "MinGW Makefiles"

pause
