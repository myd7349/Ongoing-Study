#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import math
import os.path

import h5py


app_dir = os.path.dirname(__file__)
file_path = os.path.join(app_dir, 'a.h5')


def main():
    with h5py.File(file_path, 'w') as f:
        dataset = f.create_dataset('/group/dataset', shape=(3,4), dtype='i')

        dataset[:] = [[1,2,3,4], [5,6,7,8], [9,10,11,12]]

        dataset.attrs['double'] = math.pi

        hello = '早上好！'
        dataset.attrs['string-vlen'] = hello

        hello_utf8 = hello.encode('utf-8')
        hello_ascii = 'Hello, world!'

        dataset.attrs.create('string-ascii', hello_ascii, None, '<S{0}'.format(len(hello_ascii)))

        utf8_type = h5py.string_dtype('utf-8', len(hello_utf8))
        # HDFView can not display the value of this attribute correctly, ViTables can.
        dataset.attrs.create('string', hello_utf8, None, utf8_type)

        dataset.attrs['boolean'] = True

        color_dt = h5py.enum_dtype({"RED": 0, "GREEN": 1, "BLUE": 42}, basetype='i')
        dataset.attrs.create('color', 42, dtype=color_dt)


if __name__ == '__main__':
    main()


# References:
# [set scalar fixed length string attribute in hdf5](https://stackoverflow.com/questions/47358133/set-scalar-fixed-length-string-attribute-in-hdf5)
# [Support for fixed-width UTF-8 strings](https://github.com/h5py/h5py/issues/429)
# https://docs.h5py.org/en/stable/special.html
# https://github.com/PyTables/PyTables/blob/master/tables/tests/test_enum.py
