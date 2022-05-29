#!/usr/bin/env python3
# coding: utf-8

import os.path
import urllib.request

import cppimport.import_hook
import pocketfft


POCKET_FFT_SOURCES = 'pocketfft.c', 'pocketfft.h'


same_dir = lambda entry: os.path.join(os.path.dirname(__file__), entry)


def download_pocketfft():
    url = 'https://raw.githubusercontent.com/mreineck/pocketfft/master/'
    for source in POCKET_FFT_SOURCES:
        if not os.path.isfile(same_dir(source)):
            urllib.request.urlretrieve(url + source, same_dir(source))


def main():
    download_pocketfft()

    print(dir(pocketfft))


if __name__ == '__main__':
    main()


# References:
# [Pybind11: Wrap a struct with a pointer member?](https://stackoverflow.com/questions/68292760/pybind11-wrap-a-struct-with-a-pointer-member)
# [returning numpy arrays via pybind11](https://stackoverflow.com/questions/44659924/returning-numpy-arrays-via-pybind11)
