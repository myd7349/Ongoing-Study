echo Build and install libfoo ...
cd "%~dp0"
mkdir build-libfoo
cd build-libfoo
cmake ../.. -DBUILD_SHARED_LIBS=ON -DBUILD_STATIC_LIBS=OFF -DCMAKE_INSTALL_PREFIX="%~dp0build-libfoo\libfoo"
cmake --build . --target install
cd ..
