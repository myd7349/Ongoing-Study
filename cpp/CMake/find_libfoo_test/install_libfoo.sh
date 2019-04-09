#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

cd "$DIR"

if [ ! -d "$DIR/build/libfoo" ]; then
    echo Installing libfoo ...
    pushd "$DIR/../libfoo"
    mkdir build
    pushd build
    cmake .. -DBUILD_SHARED_LIBS=ON -DBUILD_STATIC_LIBS=OFF -DCMAKE_INSTALL_PREFIX="$DIR/build/libfoo"
    cmake --build . --target install
    popd
    popd
fi

# References:
# https://stackoverflow.com/questions/59838/check-if-a-directory-exists-in-a-shell-script

