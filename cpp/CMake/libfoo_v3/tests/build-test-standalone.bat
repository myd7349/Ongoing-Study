call "%~dp0install-libfoo.bat"

echo Run test ...
cd "%~dp0"
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX="%~dp0build-libfoo\libfoo"
cmake --build . --target foo_test
ctest . -C Debug
cd ..
pause