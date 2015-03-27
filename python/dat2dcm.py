#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-03-23T14:34+08:00
# myd7349@gmail.com

__version__ = '0.0.1'

import io
import math
import os
import struct
import warnings

import dicom # [pydicom](http://www.pydicom.org/)

import fileutil
import numutil

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
    else:
        if not hasattr(fp, 'read'):
            raise ValueError('Invalid file object')
        if hasattr(fp, 'mode') and fp.mode != 'rb':
            raise ValueError('Invalid opening mode')

    with fileutil.open_file(f, 'rb') as fp:
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

class DCMECGDataset(dicom.dataset.Dataset):    
    def __init__(self, file, fmt, sampling_frequency, channels, channel_labels,
                 *args, **kwargs):
        '''Represents a DICOM waveform data set, with necessary attributed added.

        file: An opened file object or a file name represents a file on the disk.
        fmt: Format specification for unpacking data from file.
        sampling_frequency: Sampling frequency of the data.
        channels: Number of channels.
        channel_labels: An iterable object that contains labels for each channel.
        '''
        super().__init__(*args, **kwargs)

        self._file = file
        self._format = fmt
        self._sampling_frequency = numutil.to_int(sampling_frequency)
        self._channels = numutil.to_int(channels)
        self._channel_label = channel_labels

        # The format of DICOM file is described in:
        #   PS3.10 7.1 DICOM File Meta Information
        # The 12-Lead ECG IOD is described in:
        #   PS3.3 A.34.3.1 12-Lead ECG IOD Description

        # To make things simple, when generating DICOM-ECG waveform files:
        # 1. We only care those modules that are mandatory;
        # 2. We pay most of our attention on those attributes of type 1 and 2;
        
        # 1. DICOM File Meta Information
        self._fill_file_meta_info()
        # 2. Patient IE
        self._fill_patient_IE()
        # 3. Study IE
        self._fill_study_IE()
        # 4. Series IE
        self._fill_series_IE()
        # 5. Frame of Reference IE
        # 6. Equipment IE
        self._fill_equipment_IE()
        # 7. Waveform IE
        self._fill_waveform_IE()

    def _fill_file_meta_info(self):
        #----------------------------------------------------------------------
        # 1. File Preamble. Please refer save_as's docstring.
        #----------------------------------------------------------------------
        # 2. DICOM Prefix. Please refer save_as's docstring.
        #----------------------------------------------------------------------
        # 3. File Meta Information Group
        # dicom.filewriter._write_file_meta_info will add the following two
        # elements for us:
        #   FileMetaInformationGroupLength
        #   FileMetaInformationVersion

        # PS3.4 B.5 Standard SOP Classes. For 12-Lead ECG, we use:
        self.MediaStorageSOPClassUID = '1.2.840.10008.5.1.4.1.1.9.1.1'

        self.MediaStorageSOPInstanceUID = dicom.UID.generate_uid() # ???

        # PS3.5 A.2 DICOM Little Endian Transfer Syntax (Explicit VR)
        self.TransferSyntaxUID = dicom.UID.ExplicitVRLittleEndian
        
        self.ImplementationClassUID = dicom.UID.generate_uid() # ???
        #----------------------------------------------------------------------

    def _fill_patient_IE(self):
        #----------------------------------------------------------------------
        # 1. Patient(M)
        self.PatientName = '^' # Type 2
        self.PatientID = '' # Type 2
        self.PatientBirthDate = '' # Type 2. YYYYMMDD
        self.PatientSex = '' # Type 2. M(ale)/F(emale)/O(ther)
        #----------------------------------------------------------------------
        # 2. Clinical Trial Subject(U)
        #----------------------------------------------------------------------

    def _fill_study_IE(self):
        #----------------------------------------------------------------------
        # 1. General Study(M)

        # PS3.3 C.7.2.1 General Study Module tells us the Tag of Study Instance UID.
        # PS3.6 6 Registry of DICOM Data Elements tells us the VR of it: UI.
        # PS3.5 6.2 Value Representation (VR) tells us the meaning of UI and how to
        # generate a UID.
        self.StudyInstanceUID = dicom.UID.generate_uid() # Type 1
        self.StudyDate = '' # Type 2
        self.StudyTime = '' # Type 2
        self.ReferringPhysicianName = '^' # Type 2
        self.StudyID = '' # Type 2
        self.AccessionNumber = ''
        #----------------------------------------------------------------------
        # 2. Patient Study(U)
        self.AdmittingDiagnosesDescription = '' # Type 3
        self.PatientAge = 0 # Type 3
        self.PatientSize = 0 # Type 3
        self.PatientWeight = 0 # Type 3
        self.AdditionalPatientHistory = '' # Type 3
        #----------------------------------------------------------------------
        # 3. Clinical Trial Study(U)
        #----------------------------------------------------------------------

    def _fill_series_IE(self):
        #----------------------------------------------------------------------
        # 1. General Series(M)
        self.Modality = 'ECG' # Type 1. DICOM PS3.3-2015a A.34.3.4.1
        self.SeriesInstanceUID = '' # Type 1
        self.SeriesNumber = '' # (0020,0011), Type 2
        #----------------------------------------------------------------------
        # 2. Clinical Trial Series(U)
        #----------------------------------------------------------------------

    def _fill_equipment_IE(self):
        #----------------------------------------------------------------------
        # 1. General Equipment(M)
        self.Manufacturer = '' # Type 2
        self.InstitutionName = '' # Type 3
        self.InstitutionAddress = '' # Type 3
        self.SoftwareVersions = __version__ # Type 3
        self.InstitutionalDepartmentName = '' # Type 3
        #----------------------------------------------------------------------

    def _generate_channel_definition_sequence(self):
        channel_def_seq = dicom.dataset.Dataset()
        
        channel_def_seq.ChannelLabel = '' # Type 3
        channel_def_seq.ChannelSourceSequence = '' # Type 1
        channel_def_seq.ChannelSourceModifiersSequence = '' # Type 1C.
        channel_def_seq.ChannelSensitivity = '' # Type 1C
        channel_def_seq.ChannelSensitivityUnitsSequence = '' # Type 1C
        channel_def_seq.ChannelSensitivityCorrectionFactor = 100 # Type 1C
        channel_def_seq.ChannelBaseline = 0 # Type 1C
        channel_def_seq.ChannelTimeSkew = 0 # Type 1C
        channel_def_seq.WaveformBitsStored = 0 # Type 1
        channel_def_seq.FilterLowFrequency = 0 # Type 3
        channel_def_seq.FilterHighFrequency = 0 # Type 3
        channel_def_seq.NotchFilterFrequency = 0 # Type 3
        channel_def_seq.NotchFilterBandwidth = 0 # Type 3
        channel_def_seq.ChannelMinimumValue = 0 # Type 3 PS3.3 C.10.9.1.4.5 
        channel_def_seq.ChannelMaximumValue = 0 # Type 3

        return channel_def_seq
    
    def _generate_waveform_sequence(self):
        maximum_waveform_sequences = 5 # PS3.3 A.34.3.4.3 Waveform Sequence
        maximum_waveform_samples = 16384 # PS3.3 A.34.3.4.5 Number of Waveform Samples
        data_file_len = fileutil.file_size(self._file)
        pack_size = struct.calcsize(self._format)
        data_file_total_samples = data_file_len // pack_size
        if data_file_total_samples > maximum_waveform_sequences * maximum_waveform_samples:
            warnings.warn('The file is too big.' RuntimeWarning)
            data_file_total_samples = maximum_waveform_sequences * maximum_waveform_samples

        waveform_seq = dicom.sequence.Sequence()
        while data_file_total_samples > 0:
            seq_item = dicom.dataset.Dataset()
            seq_item.WaveformOriginality = 'ORIGINAL' # Type 1
            seq_item.NumberOfWaveformChannels = self._channels # Type 1. DICOM PS3.3-2015a A.34.3.4.4
            assert 1 <= seq_item.NumberOfWaveformChannels <= 13

            if data_file_total_samples >= maximum_waveform_samples:
                seq_item.NumberOfWaveformSamples = maximum_waveform_samples # Type 1
            else:
                seq_item.NumberOfWaveformSamples = data_file_total_samples
            data_file_total_samples -= seq_item.NumberOfWaveformSamples

            seq_item.SamplingFrequency = self._sampling_frequency # Type 1. DICOM PS3.3-2015a A.34.3.4.6
            seq_item.ChannelDefinitionSequence = self._generate_channel_definition_sequence() # Type 1.

            seq_item.WaveformBitsAllocated = 0 # Type 1
            seq_item.WaveformSampleInterpretation = 0 # Type 1
            seq_item.WaveformPaddingValue = 0 # Type 1C
            seq_item.WaveformData = '' # Type 1
        
        return waveform_seq

    def _fill_waveform_IE(self):
        #----------------------------------------------------------------------
        # 1. Waveform Identification(M)
        self.InstanceNumber = '' # 0x00200013. Type 1
        self.ContentDate = '' # 0x00080023. Type 1
        self.ContentTime = '' # 0x00080033. Type 1
        self.AcquisitionDateTime = '' # 0x0008002A. Type 1
        #----------------------------------------------------------------------
        # 2. Waveform(M)
        self.WaveformSequence = self._generate_waveform_sequence() # 0x54000100. Type 1
        self.WaveformDataDisplayScale = 0 # Type 3
        #----------------------------------------------------------------------
        # 3. Acquisition Context(M)
        self.AcquisitionContextSequence = 0 # 0x00400555, SQ. Type 2 T3401 ECG Acquisition Context # A.34.3.4.2
        #----------------------------------------------------------------------
        # 4. Waveform Annotation(C)
        #----------------------------------------------------------------------
        # 5. SOP Common(M)
        # PS3.3 C.12.1.1.1 SOP Class UID, SOP Instance UID
        self.SOPClassUID = self.MediaStorageSOPClassUID # Type 1
        self.SOPInstanceUID = self.MediaStorageSOPInstanceUID # Type 1
        # PS3.3 C.12.1.1.2 Specific Character Set
        self.SpecificCharacterSet = 'GBK' # Type 1C
        self.TimezoneOffsetFromUTC = '+0800' # Type 3
        #----------------------------------------------------------------------
    
    def save_as(self, filename):
        '''dicom.dataset.Dataset.save_as calls dicom.filewriter.write_file to do
        the real work. And the latter calls dicom.filewriter._write_file_meta_info
        to write the file meta information. When no preamble is provided and
        write_like_original is set as False,  _write_file_meta_info will write
        the preamble and DICOM prefix for us.
        '''
        super().save_as(filename, write_like_original = False)
    
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
    data_set = DCMECGDataset()

    # Data format:
    # Lead I, II, III, aVR, aVL, aVF, V1, V2, V3, V4, V5, V6, I, II, III, ...
    #_data_to_dcm(src, '@{}'.format('d' * 12), dest)

if __name__ == '__main__':
    ecg_to_dcm('', 'c:\test2.dcm')

# References:
# DICOM 2015a PS3.5 7.4 Data Element Type
# DICOM 2015a PS3.5 8.3 Waveform Data and Related Data Elements
# DICOM 2015a PS3.6 6 Registry of DICOM Data Elements
# [DICOM Waveform Generator](http://libir.tmu.edu.tw/bitstream/987654321/21661/1/B09.pdf)
# [Mandatory Tags for DICOM Instance](http://stackoverflow.com/questions/6608535/mandatory-tags-for-dicom-instance)
# [PEP8](https://www.python.org/dev/peps/pep-0008/)
# [Questions regarding the DICOM file](http://fixunix.com/dicom/50267-questions-regarding-dicom-file.html)
# [Dicom: What's the point of SOPInstanceUID tag?](http://stackoverflow.com/questions/1434918/dicom-whats-the-point-of-sopinstanceuid-tag)
