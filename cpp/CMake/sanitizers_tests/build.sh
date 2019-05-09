#!/bin/bash

mkdir build
pushd build
cmake .. -DSANITIZE_ADDRESS=ON -DSANITIZE_LEAKS=OFF -DSANITIZE_MEMORY=OFF
cmake --build .
./global_out_of_bounds
./heap_out_of_bounds
./stack_out_of-bounds
./use_after_free
popd

