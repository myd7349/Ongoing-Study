#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-06-12T15:37+08:00

__author__ = 'myd7349 <myd7349@gmail.com>'
__version__ = '0.0.2'

import dicom  # [pydicom](http://www.pydicom.org/)

import fileutil


class ECGDataset(dicom.dataset.FileDataset):
    """Represents a DICOM-ECG waveform data set, with necessary attributed added."""
    
    def __init__(self, file, fmt, sampling_frequency, channel_labels,
                 adjust_callback=int, is_12_lead_ecg=True, **kwargs):
        """
        file: an opened file object or a file name represents a file on the disk
        fmt: format specification for unpacking data from file
        sampling_frequency: sampling frequency of the data
        channel_labels: an iterable object that contains labels for each channel
        adjust_callback: a callback function to adjust unpacked data
        is_12_lead_ecg: True for 12-Lead ECG IOD, False for General ECG IOD
        """
        super().__init__('', {}, is_implicit_VR=False, preamble=b'\x00' * 128, **kwargs)

        self._file, self._format, self._sampling_frequency = file, fmt, sampling_frequency
        self._channel_labels = channel_labels
        self._adjust_callback = adjust_callback
        self._is_12_lead_ecg = is_12_lead_ecg

        # 1. DICOM File Meta Information
        self._fill_file_meta_info()
        # 2. Patient IE(M)
        #self._fill_patient_IE()
        # 3. Study IE(M)
        #self._fill_study_IE()
        # 4. Series IE(M)
        #self._fill_series_IE()
        # 5. Frame of Reference IE(U)
        # 6. Equipment IE(M)
        #self._fill_equipment_IE()
        # 7. Waveform IE(M)
        #self._fill_waveform_IE()

    def _fill_file_meta_info(self):
        self.file_meta = dicom.dataset.Dataset()
        # dicom.dataset.Dataset.save_as calls dicom.filewriter.write_file to do
        # the real work. And the latter calls dicom.filewriter._write_file_meta_info
        # to write the file meta information.
        # ---------------------------------------------------------------------
        # 1. File Preamble.
        # ---------------------------------------------------------------------
        # 2. DICOM Prefix.
        # ---------------------------------------------------------------------
        # 3. File Meta Information Group
        # dicom.filewriter._write_file_meta_info will add the following two
        # elements for us:
        #   FileMetaInformationGroupLength
        #   FileMetaInformationVersion

        # PS3.4 B.5 Standard SOP Classes. See PS3.4 B.5 Standard SOP Classes.
        # Note that, this program only supports 12-Lead ECG IOD and General ECG IOD currently.
        if self._is_12_lead_ecg:
            # For 12-Lead ECG, we use:
            self.file_meta.MediaStorageSOPClassUID = '1.2.840.10008.5.1.4.1.1.9.1.1'
        else:
            # Otherwise, suppose that it is General Electrocardiogram IOD. So we use:
            self.file_meta.MediaStorageSOPClassUID = '1.2.840.10008.5.1.4.1.1.9.1.2'

        self.file_meta.MediaStorageSOPInstanceUID = '1.3.6.1.4.1.6018.1.1' # ???

        # PS3.5 A.2 DICOM Little Endian Transfer Syntax (Explicit VR)
        self.file_meta.TransferSyntaxUID = dicom.UID.ExplicitVRLittleEndian
        
        self.file_meta.ImplementationClassUID = '1.3.6.1.4.1.6018.2.11111' # ???
        # ---------------------------------------------------------------------


def ecg_to_dcm(src, dest=None):
    """Convert 12-Lead Electrocardiogram data into DICOM-ECG standard compliant format."""
    # Data values are encoded interleaved. That is:
    # Lead I, II, III, aVR, aVL, aVF, V1, V2, V3, V4, V5, V6, I, II, III, ...
    # The unit of signals collected by the cardiac conduction is: 0.4V/(2^15).
    if not dest:
        dest = fileutil.replace_ext(src, '.dcm')


def fecg_to_dcm(src, dest=None):
    pass


def test():
    pass


if __name__ == '__main__':
    test()
