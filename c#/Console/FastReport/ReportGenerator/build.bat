call RestoreNuGetPackages.bat
mkdir build
pushd build
cmake ..
cmake --build . --config Release
popd
pause
