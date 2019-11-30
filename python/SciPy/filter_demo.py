#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from matplotlib.pyplot import plot
import numpy as np
from scipy.signal import lfilter


data = np.arange(1.0, 4.0 + 0.2, 0.2)
window_size = 5
result = lfilter(
    np.ones(window_size) / window_size,
    1,
    data)

print(np.dot([[3,1], [1,2]], [2,3]))

print(result)
plot(result)


# References:
# https://dsp.stackexchange.com/questions/11466/differences-between-python-and-matlab-filtfilt-function
# MATLAB: doc filter
# https://stackoverflow.com/questions/37571622/matlab-range-in-python
