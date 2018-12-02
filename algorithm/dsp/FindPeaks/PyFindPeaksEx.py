#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import math
import os.path
import urllib.request

import numpy as np

root_dir = os.path.dirname(__file__)
same_dir = lambda entry: os.path.join(root_dir, entry)

if not os.path.isfile(same_dir('detect_peaks.py')):
    urllib.request.urlretrieve(
        'https://raw.githubusercontent.com/demotu/BMC/master/functions/detect_peaks.py',
        same_dir('detect_peaks.py'))

import detect_peaks


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
        
    ind = m.FindPeaks(x.tolist(), math.nan if mph == None else mph, mpd, threshold, edge_type, kpsh, valley)
    ind = np.array(ind)
    
    if show:
       detect_peaks._plot(x, mph, mpd, threshold, edge, valley, ax, np.array(ind))

    return ind
