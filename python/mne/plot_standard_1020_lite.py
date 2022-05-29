#!/usr/bin/env python3
# coding: utf-8

from collections import OrderedDict
from pprint import pprint

import mne.channels

pprint(mne.channels.get_builtin_montages())

standard_1020_montage = mne.channels.make_standard_montage('standard_1020')

pprint(standard_1020_montage.get_positions())

ch_pos = standard_1020_montage.get_positions()['ch_pos']
pprint(ch_pos)

channels = frozenset((
    'Fp1', 'Fp2',
    'F7', 'F3', 'Fz', 'F4', 'F8',
    'T3', 'C3', 'Cz', 'C4', 'T4',
    'A1', 'A2', 'M1', 'M2',
    'T5', 'P3', 'Pz', 'P4', 'T6',
    'O1', 'O2',
))

channels_pos = OrderedDict()
for ch, pos in ch_pos.items():
    if ch in channels:
        channels_pos[ch] = pos

pprint(channels_pos)

standard_1020_montage.plot(
    show_names=channels,
    show=False)
standard_1020_montage.plot(
    sphere='eeglab',
    show_names=channels,
    show=False)


# References:
# https://mne.tools/0.24/auto_examples/visualization/eeglab_head_sphere.html
# Calculate sphere origin and radius
# EEGLAB plots head outline at the level where the head circumference is measured in the 10-20 system (a
# line going through Fpz, T8/T4, Oz and T7/T3 channels). MNE-Python places the head outline lower on the
# z dimension, at the level of the anatomical landmarks LPA, RPA, and NAS. Therefore to use the EEGLAB 
# layout we have to move the origin of the reference sphere (a sphere that is used as a reference when 
# projecting channel locations to a 2d plane) a few centimeters up.
