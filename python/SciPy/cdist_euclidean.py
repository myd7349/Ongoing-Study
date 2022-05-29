#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from collections import OrderedDict
import math

import numpy as np
from scipy.spatial.distance import cdist

try:
    import mne.channels
    has_mne = True
except ImportError:
    has_mne = False


def _euclidean(x, y):
    return math.sqrt(sum((pow(xi - yi, 2) for xi, yi in zip(x, y))))


def cdist_euclidean(a, b):
    XA = np.asarray(a)
    XB = np.asarray(b)

    XA_shape = np.shape(XA)
    XB_shape = XB.shape

    if len(XA_shape) != 2:
        raise ValueError('XA must be a 2-dimensional array.')
    if len(XB_shape) != 2:
        raise ValueError('XB must be a 2-dimensional array.')
    if XA_shape[1] != XB_shape[1]:
        raise ValueError('XA and XB must have the same number of columns '
                         '(i.e. feature dimension.)')

    #out = np.zeros(shape=(XA_shape[0], XB_shape[0]))
    out = np.ndarray(shape=(XA_shape[0], XB_shape[0]), dtype=float)

    for r in range(out.shape[0]):
        for c in range(out.shape[1]):
            out[r][c] = _euclidean(XA[r], XB[c])

    return out


def basic_test():
    a = ((1, 2, 3), (4, 5, 6))
    b = ((1, 2, 3), (4, 5, 6), (7, 8, 9), (10, 11, 12))

    print(cdist_euclidean(a, b))
    print(cdist(a, b))
    print(cdist(a, b) == cdist_euclidean(a, b))

    result = cdist(a, b)
    result[np.triu_indices(result.shape[0])] = np.nan
    print(result)


def elec_pos_test():
    if not has_mne:
        return

    standard_1020_montage = mne.channels.make_standard_montage('standard_1020')
    ch_pos = standard_1020_montage.get_positions()['ch_pos']

    channels = frozenset((
        'Fp1',
        'Fp2',
        'F7',
        'F3',
        'Fz',
        'F4',
        'F8',
        'T3',
        'C3',
        'Cz',
        'C4',
        'T4',
        'A1',
        'A2',
        'M1',
        'M2',
        'T5',
        'P3',
        'Pz',
        'P4',
        'T6',
        'O1',
        'O2',
    ))

    channels_pos = OrderedDict()
    for ch, pos in ch_pos.items():
        if ch in channels:
            channels_pos[ch] = pos

    channel_pos_values = np.asarray(tuple(channels_pos.values()))
    print(channel_pos_values)

    result1 = cdist(channel_pos_values, channel_pos_values)
    result2 = cdist_euclidean(channel_pos_values, channel_pos_values)
    print(result2)
    print(np.array_equal(result1, result2))


def main():
    basic_test()
    elec_pos_test()


if __name__ == '__main__':
    main()


# References:
# https://numpy.org/doc/stable/reference/generated/numpy.shape.html
# https://numpy.org/doc/stable/reference/generated/numpy.ndarray.strides.html
# Ongoing-Study/python/notes/scipy.md
# https://github.com/mne-tools/mne-python/blob/v1.0.3/mne/viz/montage.py#L52
