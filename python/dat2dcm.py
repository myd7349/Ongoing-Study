#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-03-23T14:34+08:00
# myd7349@gmail.com

__version__ = '0.0.1'

import io
import struct

import dicom # [pydicom](http://www.pydicom.org/)

import fpsize

def _unpack_data(buf, fmt):
    '''Retrieve data from given data buffer and unpack them according to specified format.'''
    
    if not isinstance(buf, (bytes, bytearray)):
        raise ValueError('Invalid data buffer')

    return _unpack_data_from_file(io.BytesIO(buf), fmt)
    
def _unpack_data_from_file(fp, fmt):
    '''Retrieve data from given file object and unpack them according to specified format.

    fp: File object to work with
    fmt: Format specificaion
    '''

    if not hasattr(fp, 'read'):
        raise ValueError('Invalid file object')

    if hasattr(fp, 'mode') and fp.mode != 'rb':
        raise ValueError('Invalid opening mode')

    file_len = fpsize.fp_size(fp)
    pack_size = struct.calcsize(fmt)
    
    if file_len % pack_size == 0:
        return struct.iter_unpack(fmt, fp.read())
    else:
        # The length of the file isn't the multiple of struct.calcsize(fmt), so
        # don't calling struct.iter_unpack directly. 
        data = fp.read(pack_size)
        while data:
            if len(data) == pack_size:
                yield struct.unpack(fmt, data)
            data = fp.read(pack_size)
    
def _data_to_dcm(src, fmt, dest):
    '''Convert binary data file into DICOM-ECG standard compliant format.

    src: Source file to work with.
    fmt: Format specification used to unpack data.
    dest: Destination DICOM file to be saved as.
    strict: 
    '''
    
    if not os.path.isfile(src):
        raise ValueError('Source file "{}" is not a regular file'.format(src))

    with open(src, mode = 'rb') as fp:
        for channels_data in _unpack_data_from_file(fp, fmt):
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



