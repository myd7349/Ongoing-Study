#!/bin/bash

mkdir build
pushd build
cmake ..
cmake --build .
./pow_example
popd
