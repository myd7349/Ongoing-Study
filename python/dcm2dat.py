#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-03-30T10:13+08:00

if __name__ == '__main__':
    import dicom

    data_set = dicom.read_file(r'e:\12 lead ECG .dcm')
    with open(r'e:\12-Lead_ECG.dat', 'wb') as fp:
        for waveform_item in data_set.WaveformSequence:
            fp.write(waveform_item.WaveformData)
