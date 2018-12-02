#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np

import PyFindPeaksEx
import detect_peaks


def main():
    x = np.random.randn(100)
    x[60:81] = np.nan
    x[-1] = 20
    
    peaks1 = PyFindPeaksEx.find_peaks(x, show=True)
    peaks2 = detect_peaks.detect_peaks(x, show=True)
    
    print(peaks1)
    print(peaks2)
    assert(np.array_equal(peaks1, peaks2))
    
    peaks1 = PyFindPeaksEx.find_peaks(x, mpd=5, valley=True, show=True)
    peaks2 = detect_peaks.detect_peaks(x, mpd=5, valley=True, show=True)
    
    print(peaks1)
    print(peaks2)
    assert(np.array_equal(peaks1, peaks2))


if __name__ == '__main__':
    main()
