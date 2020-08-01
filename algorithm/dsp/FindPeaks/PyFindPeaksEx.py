#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import math
import os.path

from detecta.detect_peaks import _plot  # pip install detecta, https://github.com/demotu/detecta
import numpy as np

root_dir = os.path.dirname(__file__)
same_dir = lambda entry: os.path.join(root_dir, entry)


def find_peaks(x, mph=None, mpd=1, threshold=0, edge='rising',
    kpsh=False, valley=False, show=False, ax=None):
    import cppimport
    m = cppimport.imp('PyFindPeaks')
    
    edge_type = m.EdgeRising
    if edge == None:
        edge_type = m.EdgeNone
    elif edge == 'falling':
        edge_type = m.EdgeFalling
    elif edge == 'both':
        edge_type = m.EdgeBoth

    x = np.atleast_1d(x).astype('float64')
    ind = m.FindPeaks(x.tolist(), math.nan if mph == None else mph, mpd, threshold, edge_type, kpsh, valley)
    ind = np.array(ind)
    
    if show:
        _plot(x, mph, mpd, threshold, edge, valley, ax, np.array(ind), 'FindPeaks(C++)')

    return ind


# References:
# [How to import private functions with import *?](https://stackoverflow.com/questions/42950256/how-to-import-private-functions-with-import)
