#!/usr/bin/env python3
# coding: utf-8

import numpy as np


a = np.ones((3, 4))
print(a)
print(np.triu_indices(a.shape[0]))

a[np.triu_indices(a.shape[0])] = np.nan
print(a)


# References:
# https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/viz/montage.py#L52
# https://numpy.org/doc/stable/reference/generated/numpy.tril_indices.html
