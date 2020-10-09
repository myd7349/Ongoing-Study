mkdir build
cd build
::cmake .. --trace-expand
::cmake ..
cmake .. -G "Visual Studio 16 2019" -A Win32
cd ..
pause
