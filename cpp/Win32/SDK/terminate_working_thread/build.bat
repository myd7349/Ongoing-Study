mkdir build
pushd build
cmake .. -DCMAKE_GENERATOR_PLATFORM=Win32
cmake --build . --config Release
Release\terminate_working_thread.exe
popd
