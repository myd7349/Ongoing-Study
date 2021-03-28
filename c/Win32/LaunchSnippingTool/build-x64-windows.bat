mkdir build-x64-windows
pushd build-x64-windows
cmake .. -DCMAKE_GENERATOR_PLATFORM=x64
cmake --build . --config Release
Release\LaunchSnippingTool.exe
popd
pause
