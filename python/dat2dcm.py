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
            #return struct.iter_unpack(fmt, fp.read()) # ???
            yield from struct.iter_unpack(fmt, fp.read())
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

# PS3.16 CID 3001 ECG Leads
CID_3001_old = {
    'I': ('2:1', 'LEAD I'),
    'II': ('2:2', 'LEAD II'),
    'III': ('2:61', 'LEAD III'),
    'aVR': ('2:62', 'aVR, augmented voltage, right'),
    'aVL': ('2:63', 'aVL, augmented voltage, left'),
    'aVF': ('2:64', 'aVF, augmented voltage, foot'),
    'V1': ('2:3', 'LEAD V1'),
    'V2': ('2:4', 'LEAD V2'),
    'V3': ('2:5', 'LEAD V3'),
    'V4': ('2:6', 'LEAD V4'),
    'V5': ('2:7', 'LEAD V5'),
    'V6': ('2:8', 'LEAD V6'),
    }

CID_3001 = {
    'I': ('5.6.3-9-1', 'Lead I'),
    'II': ('5.6.3-9-2', 'Lead II'),
    'III': ('5.6.3-9-61', 'Lead III'),
    'aVR': ('5.6.3-9-62', 'Lead aVR'),
    'aVL': ('5.6.3-9-63', 'Lead aVL'),
    'aVF': ('5.6.3-9-64', 'Lead aVF'),
    'V1': ('5.6.3-9-3', 'Lead V1'),
    'V2': ('5.6.3-9-4', 'Lead V2'),
    'V3': ('5.6.3-9-5', 'Lead V3'),
    'V4': ('5.6.3-9-6', 'Lead V4'),
    'V5': ('5.6.3-9-7', 'Lead V5'),
    'V6': ('5.6.3-9-8', 'Lead V6'),
    }

class DCMECGDataset(dicom.dataset.FileDataset):    
    def __init__(self, file, fmt, sampling_frequency, channels, channel_labels,
                 *args, **kwargs):
        '''Represents a DICOM waveform data set, with necessary attributed added.

        file: An opened file object or a file name represents a file on the disk.
        fmt: Format specification for unpacking data from file.
        sampling_frequency: Sampling frequency of the data.
        channels: Number of channels.
        channel_labels: An iterable object that contains labels for each channel.
        '''
        super().__init__('', {}, is_implicit_VR = False, *args, **kwargs)

        self._file = file
        self._format = fmt
        self._sampling_frequency = sampling_frequency
        self._channels = channels
        self._channel_labels = channel_labels

        # The format of DICOM file is described in:
        #   PS3.10 7.1 DICOM File Meta Information
        # The 12-Lead ECG IOD is described in:
        #   PS3.3 A.34.3.1 12-Lead ECG IOD Descriptionfile, fmt, sampling_frequency, channels, channel_labels

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
        self.file_meta = dicom.dataset.Dataset() 
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
        self.file_meta.MediaStorageSOPClassUID = '1.2.840.10008.5.1.4.1.1.9.1.1'

        self.file_meta.MediaStorageSOPInstanceUID = dicom.UID.generate_uid() # ???

        # PS3.5 A.2 DICOM Little Endian Transfer Syntax (Explicit VR)
        self.file_meta.TransferSyntaxUID = dicom.UID.ExplicitVRLittleEndian
        
        self.file_meta.ImplementationClassUID = dicom.UID.generate_uid() # ???
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
        self.StudyInstanceUID = dicom.UID.generate_uid() # Type 1. UI.
        self.StudyDate = '' # Type 2. DA.
        self.StudyTime = '' # Type 2. TM.
        self.ReferringPhysicianName = '^' # Type 2. PN.
        self.StudyID = '' # Type 2. SH.
        self.AccessionNumber = '' # Type 2. SH.
        #----------------------------------------------------------------------
        # 2. Patient Study(U)
        self.AdmittingDiagnosesDescription = '' # Type 3. LO.
        self.PatientAge = '018Y' # Type 3. AS.
        self.PatientSize = '0' # Type 3. DS.
        self.PatientWeight = '0' # Type 3. DS.
        self.AdditionalPatientHistory = '' # Type 3. LT.
        #----------------------------------------------------------------------
        # 3. Clinical Trial Study(U)
        #----------------------------------------------------------------------

    def _fill_series_IE(self):
        #----------------------------------------------------------------------
        # 1. General Series(M)
        self.Modality = 'ECG' # Type 1. DICOM PS3.3-2015a A.34.3.4.1
        self.SeriesInstanceUID = dicom.UID.generate_uid() # Type 1. UI. ???
        self.SeriesNumber = '' # (0020,0011), Type 2. IS.
        #----------------------------------------------------------------------
        # 2. Clinical Trial Series(U)
        #----------------------------------------------------------------------

    def _fill_equipment_IE(self):
        #----------------------------------------------------------------------
        # 1. General Equipment(M)
        self.Manufacturer = '' # Type 2. LO.
        self.InstitutionName = '' # Type 3. LO.
        self.InstitutionAddress = '' # Type 3. ST.
        self.SoftwareVersions = __version__ # Type 3. LO.
        self.InstitutionalDepartmentName = '' # Type 3. LO.
        #----------------------------------------------------------------------

    def _generate_channel_source_sequence(self, label):
        # PS3.3 A.34.3.4.7 Channel Source
        channel_source_seq = dicom.dataset.Dataset()
        channel_source_seq.CodeValue = CID_3001[label][0] # Type 1C. SH.
        channel_source_seq.CodingSchemeDesignator = 'SCPECG'#'MDC' # Type 1C. SH.
        channel_source_seq.CodingSchemeVersion = '1.3' # Type 1C. SH.
        channel_source_seq.CodeMeaning = CID_3001[label][1] # Type 1. LO.

        return (channel_source_seq, )

    def _generate_channel_sensitivity_units_sequence(self):
        # I don't how to fill this part, so follow GE's step.
        sensitivity_unit_seq = dicom.dataset.Dataset()
        sensitivity_unit_seq.CodeValue = 'mV' # SH.
        sensitivity_unit_seq.CodingSchemeDesignator = 'UCUM'
        sensitivity_unit_seq.CodingSchemeVersion = '1.4' # Type 1C. SH.
        sensitivity_unit_seq.CodeMeaning = 'millivolt'

        return (sensitivity_unit_seq, )

    def _generate_channel_definition_sequence(self):
        channel_def_seq = dicom.sequence.Sequence()

        assert len(self._channel_labels) >= self._channels
        for c in range(self._channels):
            channel_def_item = dicom.dataset.Dataset()
            
            channel_def_item.ChannelLabel = self._channel_labels[c] # Type 3. SH.
            channel_def_item.ChannelSourceSequence = self._generate_channel_source_sequence(self._channel_labels[c]) # Type 1
            channel_def_item.ChannelSensitivity = '0.00122' # Type 1C. DS.
            channel_def_item.ChannelSensitivityUnitsSequence = self._generate_channel_sensitivity_units_sequence() # Type 1C
            channel_def_item.ChannelSensitivityCorrectionFactor = '1' # Type 1C. DS. ?
            channel_def_item.ChannelBaseline = '0' # Type 1C. DS.
            channel_def_item.ChannelTimeSkew = '0' # Type 1C. DS. ?
            channel_def_item.WaveformBitsStored = 16 # Type 1. US. PS3.3 C.10.9.1.5 Waveform Bits Allocated and Waveform Sample Interpretation
            channel_def_item.FilterLowFrequency = '.05' # Type 3. DS. ?
            channel_def_item.FilterHighFrequency = '100' # Type 3. DS. ?
            #channel_def_item.NotchFilterFrequency = 0 # Type 3
            #channel_def_item.NotchFilterBandwidth = 0 # Type 3
            #channel_def_item.ChannelMinimumValue = 0 # Type 3 PS3.3 C.10.9.1.4.5 C.10.9.1.6
            #channel_def_item.ChannelMaximumValue = 0 # Type 3

            channel_def_seq.append(channel_def_item)

        return channel_def_seq
    
    def _generate_waveform_sequence(self):
        maximum_waveform_sequences = 5 # PS3.3 A.34.3.4.3 Waveform Sequence
        maximum_waveform_samples = 16384 # PS3.3 A.34.3.4.5 Number of Waveform Samples
        data_file_len = fileutil.file_size(self._file)
        pack_size = struct.calcsize(self._format)
        data_file_total_samples = data_file_len // pack_size
        if data_file_total_samples > maximum_waveform_sequences * maximum_waveform_samples:
            warnings.warn('The file is too big.', RuntimeWarning)
            data_file_total_samples = maximum_waveform_sequences * maximum_waveform_samples

        waveform_seq = dicom.sequence.Sequence()
        data_unpacker = unpack_data_from_file(self._file, self._format)
        while data_file_total_samples > 0:
            seq_item = dicom.dataset.Dataset()
            seq_item.WaveformOriginality = 'ORIGINAL' # Type 1
            
            seq_item.NumberOfWaveformChannels = self._channels # Type 1. 
            assert 1 <= seq_item.NumberOfWaveformChannels <= 13 # DICOM PS3.3-2015a A.34.3.4.4

            if data_file_total_samples >= maximum_waveform_samples:
                seq_item.NumberOfWaveformSamples = maximum_waveform_samples # Type 1. UL.
            else:
                seq_item.NumberOfWaveformSamples = data_file_total_samples # Type 1. UL.
            data_file_total_samples -= seq_item.NumberOfWaveformSamples

            assert 200 <= self._sampling_frequency <= 1000 # DICOM PS3.3-2015a A.34.3.4.6
            seq_item.SamplingFrequency = '{:d}'.format(self._sampling_frequency) # Type 1. DS.

            seq_item.ChannelDefinitionSequence = self._generate_channel_definition_sequence() # Type 1.

            seq_item.WaveformBitsAllocated = 16 # Type 1. PS3.3 C.10.9.1.5 Waveform Bits Allocated and Waveform Sample Interpretation
            seq_item.WaveformSampleInterpretation = 'SS' # Type 1. PS3.3 A.34.3.4.8 Waveform Sample Interpretation

            # The VR of `Waveform Padding Value` may be OB or OW, so:
            #seq_item.WaveformPaddingValue = b'\x00\x00'
            # will not work, instead:
            seq_item.add_new((0x5400, 0x100A), 'OW', b'\x00\x00')  # Type 1C. OB or OW.

            data = bytearray()
            for i, d in zip(range(seq_item.NumberOfWaveformSamples), data_unpacker):
                data.extend(struct.pack('<{}'.format('h' * self._channels), *d))
            #seq_item.WaveformData = bytes(data) # Type 1. OB or OW.
            seq_item.add_new((0x5400, 0x1010), 'OW', bytes(data))

            waveform_seq.append(seq_item)
        
        return waveform_seq

    def _generate_concept_name_code_sequence(self):
        # I don't know how to fill this part, so follow GE's step.
        concept_name_code_seq = dicom.dataset.Dataset()
        concept_name_code_seq.CodeValue = 'G-7293'
        concept_name_code_seq.CodingSchemeDesignator = 'SRT'
        concept_name_code_seq.CodingSchemeVersion = 'V1'
        concept_name_code_seq.CodeMeaning = 'Cardiac catheterization baseline phase'
        
        return (concept_name_code_seq, )
    
    def _generate_acquisition_context_sequence(self):
        # PS3.3 A.34.3.4.2 Acquisition Context Module
        acquisition_context_seq = dicom.dataset.Dataset()
        acquisition_context_seq.ConceptNameCodeSequence = self._generate_concept_name_code_sequence()
        return (acquisition_context_seq, )

    def _fill_waveform_IE(self):
        #----------------------------------------------------------------------
        # 1. Waveform Identification(M)
        self.InstanceNumber = '0001' # 0x00200013. Type 1. IS.
        self.ContentDate = '19991223' # 0x00080023. Type 1. DA.
        self.ContentTime = '100723' # 0x00080033. Type 1. TM.
        self.AcquisitionDateTime = '19991223100723' # 0x0008002A. Type 1. DT.
        #----------------------------------------------------------------------
        # 2. Waveform(M)
        self.WaveformSequence = self._generate_waveform_sequence() # 0x54000100. Type 1
        #self.WaveformDataDisplayScale = 0 # Type 3
        #----------------------------------------------------------------------
        # 3. Acquisition Context(M)
        self.AcquisitionContextSequence = self._generate_acquisition_context_sequence() # 0x00400555, SQ. Type 2 T3401 ECG Acquisition Context # A.34.3.4.2
        #----------------------------------------------------------------------
        # 4. Waveform Annotation(C)
        #----------------------------------------------------------------------
        # 5. SOP Common(M)
        # PS3.3 C.12.1.1.1 SOP Class UID, SOP Instance UID
        self.SOPClassUID = self.file_meta.MediaStorageSOPClassUID # Type 1
        self.SOPInstanceUID = self.file_meta.MediaStorageSOPInstanceUID # Type 1
        # PS3.3 C.12.1.1.2 Specific Character Set
        #self.SpecificCharacterSet = 'GBK' # Type 1C
        #self.TimezoneOffsetFromUTC = '+0800' # Type 3
        #----------------------------------------------------------------------
    
    def save_as(self, filename):
        '''dicom.dataset.Dataset.save_as calls dicom.filewriter.write_file to do
        the real work. And the latter calls dicom.filewriter._write_file_meta_info
        to write the file meta information. When no preamble is provided and
        write_like_original is set as False,  _write_file_meta_info will write
        the preamble and DICOM prefix for us.
        '''
        super().save_as(filename, write_like_original = False)

def fecg_to_dcm(src, dest = None):
    '''Convert Foetus Electrocardiogram data into DICOM-ECG standard compliant format.'''
    # Data values are encoded interleaved. That is:
    # lead 1, 2, 3, 4, 5, 1, 2, ...
    _data_to_dcm(src, '@{}'.format('d' * 5), dest)

def ecg_to_dcm(src, dest = None):
    '''Convert 12-Lead Electrocardiogram data into DICOM-ECG standard compliant format.'''
    # Data values are encoded interleaved. That is:
    # Lead I, II, III, aVR, aVL, aVF, V1, V2, V3, V4, V5, V6, I, II, III, ...
    data_set = DCMECGDataset(src, '@{}'.format('h' * 12), 240, 12,
                             ('I', 'II', 'III', 'aVR', 'aVL', 'aVF', 'V1', 'V2', 'V3', 'V4', 'V5', 'V6'))
    data_set.save_as(dest)

if __name__ == '__main__':
    ecg_to_dcm(r'e:\12-Lead_ECG.dat', r'd:\12-Lead_ECG.dcm')

# References:
# DICOM 2015a PS3.5 7.4 Data Element Type
# DICOM 2015a PS3.5 8.3 Waveform Data and Related Data Elements
# DICOM 2015a PS3.6 6 Registry of DICOM Data Elements
# [DICOM Waveform Generator](http://libir.tmu.edu.tw/bitstream/987654321/21661/1/B09.pdf)
# [Mandatory Tags for DICOM Instance](http://stackoverflow.com/questions/6608535/mandatory-tags-for-dicom-instance)
# [PEP8](https://www.python.org/dev/peps/pep-0008/)
# [Questions regarding the DICOM file](http://fixunix.com/dicom/50267-questions-regarding-dicom-file.html)
# [Dicom: What's the point of SOPInstanceUID tag?](http://stackoverflow.com/questions/1434918/dicom-whats-the-point-of-sopinstanceuid-tag)
