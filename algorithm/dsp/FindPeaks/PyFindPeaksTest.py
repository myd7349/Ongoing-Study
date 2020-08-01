#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import struct

import numpy as np

import PyFindPeaksEx
import detecta  # pip install detecta, https://github.com/demotu/detecta

def do_test(x, **kwargs):
    if x is None:
        x = np.random.randn(100)
        x[60:81] = np.nan
        x[-1] = 20
        
    peaks1 = PyFindPeaksEx.find_peaks(x, **kwargs)
    peaks2 = detecta.detect_peaks(x, **kwargs)

    print(peaks1)
    print(peaks2)
    if not np.array_equal(peaks1, peaks2):
        with open(r'data.txt', 'w', encoding='utf-8') as fp:
            for n in x.tolist():
                fp.write('{0}\n'.format(n))
    assert(np.array_equal(peaks1, peaks2))
    

def main():
    do_test(None, show=True)
    do_test(None, mpd=5, valley=True, show=True)
    do_test(np.sin(2*np.pi*5*np.linspace(0, 1, 200)) + np.random.randn(200)/5, 
        mph=0, mpd=20, show=True)
    do_test(np.array([0, 1, 0, 2, 0, 3, 0, 2, 0, 1, 0]),
        mpd=2, show=True)
    do_test(np.sin(2*np.pi*5*np.linspace(0, 1, 200)) + np.random.randn(200)/5, 
        mph=-1.2, mpd=20, valley=True, show=True)
    do_test([0, 1, 1, 0, 1, 1, 0], edge='both', show=True)
    do_test([0, 1, 1, 0, 1, 1, 0], edge='falling', show=True)
    do_test([0, 1, 1, 0, 1, 1, 0], edge='rising', show=True)
    do_test([0, 1, 1, 0, 1, 1, 0], edge=None, show=True)
    do_test([-2, 1, -2, 2, 1, 1, 3, 0], threshold=2, show=True)

    file = PyFindPeaksEx.same_dir(r'../../..//c#/Console/CompareArrayTest/CompareArrayTest/DeputyWave.dat')
    raw_data = open(file, 'rb').read()
    data = struct.unpack('<' + 'd' * (len(raw_data) // 8), raw_data)
    #data = [num[0] for num in struct.iter_unpack('<d', raw_data)]
    #data = list(itertools.chain.from_iterable(struct.iter_unpack('<d', raw_data)))
    do_test(np.array(data), mph=0.05, mpd=100, show=True)

if __name__ == '__main__':
    main()


# References:
# https://stackoverflow.com/questions/952914/how-to-make-a-flat-list-out-of-list-of-lists
