mkdir build-subproject
cd build-subproject
cmake .. -DBUILD_SHARED_LIBS=OFF -DJSON_C_SUBPROJECT_TEST=ON
cmake --build . --config Release
Release\json_c_test.exe
cd ..
pause
