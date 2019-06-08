#!/bin/bash

mkdir build
pushd build
cmake ..
cmake --build . --config Debug
popd
