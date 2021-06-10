#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os.path

import h5py


app_dir = os.path.dirname(__file__)
file_path = os.path.join(app_dir, 'a.h5')

def main():
    with h5py.File(file_path, 'w') as file:
        boolean_type = h5py.enum_dtype({ "False": 0, "True": 1 }, basetype='i')
        file.attrs.create('boolean', 0, None, boolean_type)

if __name__ == '__main__':
    main()


# References:
# [Special types](https://docs.h5py.org/en/stable/special.html)
