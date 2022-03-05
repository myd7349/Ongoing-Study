#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import math
import os.path

import numpy as np
import tables


app_dir = os.path.dirname(__file__)
file_path = os.path.join(app_dir, 'a.h5')


def main():
    with tables.open_file(file_path, 'w', title='Hello, PyTables!') as f:
        group = f.create_group(f.root, 'group', 'My first PyTables group')

        data = [[1,2,3,4], [5,6,7,8], [9,10,11,12]]
        array = f.create_array(group, 'dataset', np.array(data), 'My first PyTables array')

        array.attrs.double = math.pi

        hello = '你好！'
        array.attrs['hello-zh_CN'] = hello

        hello_utf8 = hello.encode('utf-8')
        hello_ascii = 'Hello, world!'

        array.attrs['string-ascii'] = hello_ascii
        array.attrs['string-utf8'] = hello_utf8

        array.attrs['boolean'] = True

        color_enum = tables.Enum({"RED": 0, "GREEN": 1, "BLUE": 42})
        array.attrs.color = color_enum.RED


if __name__ == '__main__':
    main()


# References:
# [set scalar fixed length string attribute in hdf5](https://stackoverflow.com/questions/47358133/set-scalar-fixed-length-string-attribute-in-hdf5)
# [Support for fixed-width UTF-8 strings](https://github.com/h5py/h5py/issues/429)
# https://docs.h5py.org/en/stable/special.html
# https://github.com/PyTables/PyTables/blob/master/tables/tests/test_enum.py
