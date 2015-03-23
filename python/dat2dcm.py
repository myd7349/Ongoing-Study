#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-03-23T14:34+08:00
# myd7349@gmail.com

__version__ = '0.0.1'

import os.path
import struct

import dicom # [pydicom](http://www.pydicom.org/)

def _data_to_dcm(src, fmt, dest):
    '''Convert binary data file into DICOM-ECG standard compliant format.

    src: Source file to work with
    fmt: Format specification used to unpack data
    dest: Destination DICOM file to be saved as
    '''
    
    if not os.path.isfile(src):
        raise ValueError('Source file "{}" is not a regular file.'.format(src))

    with open(src, mode = 'rb') as fp:
        for data_tuple in struct.iter_unpack(fmt, fp.read()):
            pass

def fecg_to_dcm(src, dest = None):
    '''Convert Foetus Electrocardiogram data into DICOM-ECG standard compliant format.'''

    # Data format:
    # channel 1, channel 2, channel 3, channel 4, channel 5, channel 1, channel 2, ...
    _data_to_dcm(src, '@{}'.format('d' * 5), dest)

def ecg_to_dcm(src, dest = None):
    '''Convert 12-Lead Electrocardiogram data into DICOM-ECG standard compliant format.'''

    # Data format:
    # I, II, III, AVR, AVL, AVF, V1, V2, V3, V4, V5, V6, I, II, III, ...
    _data_to_dcm(src, '@{}'.format('d' * 12), dest)

