#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import random

import matplotlib.pyplot as plt
import numpy as np

import cppimport.import_hook
import pycumsum


raw_data = \
    [random.uniform(0.0, 10.0) for i in range(1000)] + \
    [random.uniform(100.0, 200.0) for i in range(100)] + \
    [random.uniform(0.0, 10.0) for i in range(200)] + \
    [random.uniform(900.0, 1000.0) for i in range(200)]

cumsum_detector = pycumsum.CUSUMChangeDetector(0.05, 3.0, 50)

data = np.atleast_1d(raw_data).astype('float64')
indices = []

for i, xi in enumerate(data):
    if cumsum_detector.update(xi):
        cumsum_detector.reset()
        indices.append(i)

print(indices)

indices = np.array(indices)

plt.plot(data)
plt.plot(indices, data[indices], 'r+')

plt.show()


# References:
# https://stackoverflow.com/questions/41709257/how-to-change-the-plot-line-color-from-blue-to-black
# https://stackoverflow.com/questions/8409095/matplotlib-set-markers-for-individual-points-on-a-line
