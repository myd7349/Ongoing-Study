if NOT EXIST "%~dp0\build\libfoo" (
    echo Installing libfoo ...
    cd /d "%~dp0\..\libfoo"
    mkdir build
    cd build
    cmake .. -DBUILD_SHARED_LIBS=ON -DBUILD_STATIC_LIBS=OFF -DCMAKE_INSTALL_PREFIX="%~dp0\build\libfoo"
    cmake --build . --target install
)

:: References:
:: https://stackoverflow.com/questions/6241922/how-to-use-cmake-install-prefix
:: https://stackoverflow.com/questions/8019505/how-to-set-the-cmake-prefix-path
