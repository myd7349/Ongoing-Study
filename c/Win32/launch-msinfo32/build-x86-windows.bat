mkdir build-x86-windows
pushd build-x86-windows
cmake .. -DCMAKE_GENERATOR_PLATFORM=Win32
cmake --build . --config Release
Release\launch-msinfo32.exe
pushd
pause
