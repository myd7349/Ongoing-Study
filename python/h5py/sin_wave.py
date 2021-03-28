#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# $ yapf -i sin_wave.py

import os
import os.path
import timeit

import h5py
import numpy as np

app_dir = os.path.dirname(__file__)
file_path = os.path.join(app_dir, 'sin_wave.hdf5')


def main():
    if os.path.exists(file_path):
        os.remove(file_path)

    with h5py.File(file_path, 'w', userblock_size=512) as f:
        print(f.userblock_size)

        # 1. First dataset
        dataset = f.create_dataset('data', shape=(1000000, 2))
        print(dataset.shape)
        print(dataset.dtype)

        start = timeit.default_timer()

        for i in range(dataset.shape[0]):
            dataset[i, 0] = i
            dataset[i, 1] = i**2

        dataset.attrs['original'] = True

        end = timeit.default_timer()
        print('Done! It took {0} seconds.'.format(end - start))

        # 2. Second dataset
        start = timeit.default_timer()

        dataset2 = f.create_dataset('data2', shape=dataset.shape)

        data = np.empty(dataset.shape)
        for i in range(data.shape[0]):
            data[i, 0] = i
            data[i, 1] = i**2

        dataset2[:] = data

        end = timeit.default_timer()
        print('Done! It took {0} seconds.'.format(end - start))


if __name__ == '__main__':
    main()

# References:
# https://support.hdfgroup.org/HDF5/doc/cpplus_RM/extend_ds_8cpp-example.html
