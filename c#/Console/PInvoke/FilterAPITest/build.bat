mkdir build32 & pushd build32
cmake -G "Visual Studio 15 2017" ..
popd
mkdir build64 & pushd build64
cmake -G "Visual Studio 15 2017 Win64" ..
popd
cmake --build build32 --config Release
cmake --build build64 --config Release
build32\FilterAPITest\Release\FilterAPITest.exe
build64\FilterAPITest\Release\FilterAPITest.exe
pause

:: References:
:: [How to build x86 and/or x64 on Windows from command line with CMAKE?](https://stackoverflow.com/questions/28350214/how-to-build-x86-and-or-x64-on-windows-from-command-line-with-cmake?rq=1)
