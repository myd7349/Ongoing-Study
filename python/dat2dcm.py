#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-03-23T14:34+08:00
# myd7349@gmail.com

__version__ = '0.0.1'

import io
import os
import struct

import dicom # [pydicom](http://www.pydicom.org/)

import fileutil

def unpack_data(buf, fmt):
    '''Retrieve data from given data buffer and unpack them according to specified format.'''
    
    if not isinstance(buf, (bytes, bytearray)):
        raise ValueError('Invalid data buffer')
    
    return unpack_data_from_file(io.BytesIO(buf), fmt)
    
def unpack_data_from_file(f, fmt):
    '''Retrieve data from given file and unpack them according to specified format.

    f: The path name of the file or an opened file object
    fmt: Format specificaion
    '''

    if isinstance(f, str):
        if not os.path.isfile(f):
            raise ValueError('"{}" is not a regular file'.format(f))
        
        fp = open(f, 'rb')
    else:
        fp = f

        if not hasattr(fp, 'read'):
            raise ValueError('Invalid file object')
        
        if hasattr(fp, 'mode') and fp.mode != 'rb':
            raise ValueError('Invalid opening mode')

    file_len = fileutil.file_size(fp)
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
            else:
                break
            data = fp.read(pack_size)
    
def data_to_dcm(src, fmt, dest = None):
    '''Convert binary data file into DICOM-ECG standard compliant format.

    src: Source file to work with
    fmt: Format specification used to unpack data
    dest: Destination DICOM file to be saved as
    '''

    if not dest:
        dest = fileutil.replace_ext(src, '.dcm')

def fecg_to_dcm(src, dest = None):
    '''Convert Foetus Electrocardiogram data into DICOM-ECG standard compliant format.'''

    # Data format:
    # lead 1, 2, 3, 4, 5, 1, 2, ...
    _data_to_dcm(src, '@{}'.format('d' * 5), dest)

def ecg_to_dcm(src, dest = None):
    '''Convert 12-Lead Electrocardiogram data into DICOM-ECG standard compliant format.'''

    # To make things simple, when generating DICOM files:
    # 1. Only mandatory modules will be used;
    # 2. Only those attributes of type 1 and 2 will be used;

    data_set = dicom.dataset.Dataset()
    
    # The format of DICOM file is described in PS3.10 7.1.
    ############################################################################
    # 1. DICOM File Meta Information

    # 1.1 File Preamble
    # Type 1. If no preamble is provided and `write_like_original` is False,
    # dicom.filewriter.write_file will write this part for us.

    # 1.2 DICOM Prefix
    # Type 1. We would like dicom.filewriter.write_file to fill this part.

    # 1.3 File Meta Information Group

    # dicom.filewriter._write_file_meta_info will add this two data elements.
    #data_set.FileMetaInformationGroupLength
    #data_set.FileMetaInformationVersion

    # PS3.4 B.5 Standard SOP Classes. For 12-Lead ECG, we use:
    data_set.MediaStorageSOPClassUID = '1.2.840.10008.5.1.4.1.1.9.1.1'

    data_set.MediaStorageSOPInstanceUID = dicom.UID.generate_uid() # ???
    data_set.TransferSyntaxUID = dicom.UID.ExplicitVRLittleEndian
    data_set.ImplementationClassUID = dicom.UID.generate_uid() # ???

    ############################################################################
    # 2. Patient IE
    # 2.1 Patient(M)
    data_set.PatientName = '' # Type 2
    data_set.PatientID = '' # Type 2
    data_set.TypeOfPatientID = 'TEXT' 
    data_set.PatientBirthDate = '' # Type 2. YYYYMMDD
    data_set.PatientSex = '' # Type 2. M(ale)/F(emale)/O(ther)
    
    data_set.PatientAddress = ''
    # 2.2 Clinical Trial Subject(U)

    ############################################################################
    # 3. Study IE
    # 3.1 General Study(M)
    data_set.StudyInstanceUID = '' # Type 1
    data_set.StudyDate = '' # Type 2
    data_set.StudyTime = '' # Type 2
    data_set.ReferringPhysicianName = '' # Type 2
    data_set.StudyID = '' # Type 2
    data_set.AccessionNumber = ''
    # 3.2 Patient Study(U)
    data_set.PatientAge = 0 # Type 3
    data_set.PatientSize = 0 # Type 3
    data_set.PatientWeight = 0 # Type 3
    data_set.AdditionalPatientHistory = '' # Type 3
    # 3.3 Clinical Trial Study(U)

    ############################################################################
    # 4. Series IE
    # 4.1 General Series(M)
    data_set.Modality = 'ECG' # Type 1. DICOM PS3.3-2015a A.34.3.4.1
    data_set.SeriesInstanceUID = '' # Type 1
    data_set.SeriesNumber = ''
    # 4.2 Clinical Trial Series(U)

    ############################################################################
    # 5. Frame of Reference IE

    ############################################################################
    # 6. Equipment IE
    # 6.1 General Equipment(M)
    data_set.Manufacturer = '' # Type 2
    data_set.InstitutionName = '' # Type 3
    data_set.InstitutionAddress = '' # Type 3
    data_set.SoftwareVersions = __version__ # Type 3
    data_set.InstitutionalDepartmentName = '' # Type 3

    ############################################################################
    # 7. Waveform IE
    # 7.1 Waveform Identification(M)
    data_set.InstanceNumber = '' # Type 1
    data_set.ContentDate = '' # Type 1
    data_set.ContentTime = '' # Type 1
    data_set.AcquisitionDateTime = '' # Type 1
    # 7.2 Waveform(M)
    data_set.WaveformSequence = 1 # Type 1
    data_set.WaveformOriginality = 'ORIGINAL' # Type 1
    data_set.NumberOfWaveformChannels = 12 # Type 1. DICOM PS3.3-2015a A.34.3.4.4
    data_set.NumberOfWaveformSamples = 0 # Type 1
    data_set.SamplingFrequency = 500 # Type 1. DICOM PS3.3-2015a A.34.3.4.6
    data_set.ChannelDefinitionSequence = '' # Type 1.
    data_set.WaveformChannelNumber = 0 # Type 3
    data_set.ChannelLabel = '' # Type 3
    data_set.ChannelSourceSequence = '' # Type 1
    data_set.ChannelSourceModifiersSequence = '' # Type 1C.
    data_set.ChannelSensitivity = '' # Type 1C
    data_set.ChannelSensitivityUnitsSequence = '' # Type 1C
    data_set.ChannelSensitivityCorrectionFactor = 100 # Type 1C
    data_set.ChannelBaseline = 0 # Type 1C
    data_set.ChannelSampleSkew = 0 # Type 1C
    data_set.WaveformBitsStored = 0 # Type 1
    data_set.FilterLowFrequency = 0 # Type 3
    data_set.FilterHighFrequency = 0 # Type 3
    data_set.NotchFilterFrequency = 0 # Type 3
    data_set.NotchFilterBandwidth = 0 # Type 3
    data_set.ChannelMinimumValue = 0 # Type 3
    data_set.ChannelMaximumValue = 0 # Type 3
    data_set.WaveformBitsAllocated = 0 # Type 1
    data_set.WaveformSampleInterpretation = 0 # Type 1
    data_set.WaveformPaddingValue = 0 # Type 1C
    data_set.WaveformData = '' # Type 1
    data_set.WaveformDataDisplayScale = 0 # Type 3
    # 7.3 Acquisition Context(M)
    # 7.4 SOP Common(M)
    
    
    
    data_set.AcquisitionContextSequence = '' # T3401 ECG Acquisition Context # A.34.3.4.2
    
    data_set.SOPClassUID = ''
    data_set.SOPInstanceUID = data_set.MediaStorageSOPInstanceUID

    # Data format:
    # Lead I, II, III, aVR, aVL, aVF, V1, V2, V3, V4, V5, V6, I, II, III, ...
    #_data_to_dcm(src, '@{}'.format('d' * 12), dest)

if __name__ == '__main__':
    ecg_to_dcm('', 'c:\test2.dcm')

# References:
# DICOM 2015a PS3.3 A.34.3.1 12-Lead ECG IOD Description
# DICOM 2015a PS3.4 B.5 Standard SOP Classes
# DICOM 2015a PS3.5 6.2 Value Representation (VR)
# DICOM 2015a PS3.5 7.4 Data Element Type
# DICOM 2015a PS3.5 8.3 Waveform Data and Related Data Elements
# DICOM 2015a PS3.5 A.2 DICOM Little Endian Transfer Syntax (Explicit VR)
# DICOM 2015a PS3.6 6 Registry of DICOM Data Elements
# DICOM 2015a PS3.10 7.1 DICOM File Meta Information
# [DICOM Waveform Generator](http://libir.tmu.edu.tw/bitstream/987654321/21661/1/B09.pdf)
# [Mandatory Tags for DICOM Instance](http://stackoverflow.com/questions/6608535/mandatory-tags-for-dicom-instance)
# [PEP8](https://www.python.org/dev/peps/pep-0008/)
# [Questions regarding the DICOM file](http://fixunix.com/dicom/50267-questions-regarding-dicom-file.html)
# [Dicom: What's the point of SOPInstanceUID tag?](http://stackoverflow.com/questions/1434918/dicom-whats-the-point-of-sopinstanceuid-tag)
