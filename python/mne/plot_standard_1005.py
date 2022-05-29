#!/usr/bin/env python3
# coding: utf-8

import mne.channels
import mne.viz


def main():
    standard_1005_montage = mne.channels.make_standard_montage('standard_1005')
    mne.viz.plot_montage(standard_1005_montage)
    mne.viz.plot_montage(standard_1005_montage, sphere='eeglab')


if __name__ == '__main__':
    main()
