#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-06-12T15:37+08:00

__author__ = 'myd7349 <myd7349@gmail.com>'
__version__ = '0.0.2'

import struct

import dicom  # [pydicom](http://www.pydicom.org/)

import fileutil
import unpacker


_patient_IE = {
    # -------------------------------------------------------------------------
    # 1. Patient(M)
    'PatientName': '^',  # Type 2. PN.
    'PatientID': ' ',  # Type 2. LO.
    'PatientBirthDate': ' ',  # Type 2. YYYYMMDD
    'PatientSex': ' ',  # Type 2. M(ale)/F(emale)/O(ther)
    # -------------------------------------------------------------------------
    # 2. Clinical Trial Subject(U)
    # -------------------------------------------------------------------------
    }

_study_IE = {
    # -------------------------------------------------------------------------
    # 1. General Study(M)
    'StudyInstanceUID': '1.3.6.1.4.1.6018.4.999',  # Type 1. UI. ???
    'StudyDate': ' ',  # Type 2. DA.
    'StudyTime': ' ',  # Type 2. TM.
    'ReferringPhysicianName': '^',  # Type 2. PN.
    'StudyID': ' ',  # Type 2. SH.
    'AccessionNumber': ' ',  # Type 2. SH.
    # -------------------------------------------------------------------------
    # 2. Patient Study(U)
    'AdmittingDiagnosesDescription': ' ',  # Type 3. LO.
    'PatientAge': ' ',  # Type 3. AS.
    'PatientSize': ' ',  # Type 3. DS.
    'PatientWeight': ' ',  # Type 3. DS.
    'AdditionalPatientHistory': ' ',  # Type 3. LT.
    # -------------------------------------------------------------------------
    # 3. Clinical Trial Study(U)
    # -------------------------------------------------------------------------
    }

_series_IE = {
    # -------------------------------------------------------------------------
    # 1. General Series(M)
    'Modality': 'ECG',  # Type 1. DICOM PS3.3-2015a A.34.3.4.1
    'SeriesInstanceUID': ' 1.3.6.1.4.1.6018.5.999',  # Type 1. UI. ???
    'SeriesNumber': '0001',  # (0020,0011), Type 2. IS. ???
    # -------------------------------------------------------------------------
    # 2. Clinical Trial Series(U)
    # -------------------------------------------------------------------------
    }

_equipment_IE = {
    # -------------------------------------------------------------------------
    # 1. General Equipment(M)
    'Manufacturer': ' ',  # Type 2. LO.
    'InstitutionName': ' ',  # Type 3. LO.
    'InstitutionAddress': ' ',  # Type 3. ST.
    'SoftwareVersions': __version__,  # Type 3. LO.
    'InstitutionalDepartmentName': ' ',  # Type 3. LO.
    # -------------------------------------------------------------------------
    }

# PS3.16 CID 3001 ECG Leads
CID_3001_for_12_Lead_ECG = {
    'I': ('2:1', 'Lead I'),
    'II': ('2:2', 'Lead II'),
    'III': ('2:61', 'Lead III'),
    'aVR': ('2:62', 'aVR, augmented voltage, right'),
    'aVL': ('2:63', 'aVL, augmented voltage, left'),
    'aVF': ('2:64', 'aVF, augmented voltage, foot'),
    'V1': ('2:3', 'Lead V1'),
    'V2': ('2:4', 'Lead V2'),
    'V3': ('2:5', 'Lead V3'),
    'V4': ('2:6', 'Lead V4'),
    'V5': ('2:7', 'Lead V5'),
    'V6': ('2:8', 'Lead V6'),
    }


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
        # 3. Study IE(M)
        # 4. Series IE(M)
        # 5. Frame of Reference IE(U)
        # 6. Equipment IE(M)
        for IE in (_patient_IE, _study_IE, _series_IE, _equipment_IE):
            for attr in IE:
                setattr(self, attr, IE[attr])
        # 7. Waveform IE(M)
        self._fill_waveform_IE()

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

    def _fill_waveform_IE(self):
        # ---------------------------------------------------------------------
        # 1. Waveform Identification(M)
        self.InstanceNumber = ' '  # 0x00200013. Type 1. IS.
        self.ContentDate = self.StudyDate  # 0x00080023. Type 1. DA.
        self.ContentTime = self.StudyTime  # 0x00080033. Type 1. TM.
        self.AcquisitionDateTime = ' '  # 0x0008002A. Type 1. DT.
        # ---------------------------------------------------------------------
        # 2. Waveform(M)
        self.WaveformSequence = self._generate_waveform_sequence()  # 0x54000100. Type 1
        self.WaveformDataDisplayScale = 0  # Type 3
        # ---------------------------------------------------------------------
        # 3. Acquisition Context(M)
        self.AcquisitionContextSequence = ()  # 0x00400555, SQ. Type 2 T3401 ECG Acquisition Context # A.34.3.4.2
        # ---------------------------------------------------------------------
        # 4. Waveform Annotation(C)
        # ---------------------------------------------------------------------
        # 5. SOP Common(M)
        # PS3.3 C.12.1.1.1 SOP Class UID, SOP Instance UID
        self.SOPClassUID = self.file_meta.MediaStorageSOPClassUID  # Type 1 ???
        self.SOPInstanceUID = '1.3.6.1.4.1.6018.3.999'  # Type 1. ???
        # PS3.3 C.12.1.1.2 Specific Character Set
        self.SpecificCharacterSet = 'ISO_IR 192'  # Type 1C. 'ISO_IR 192' for UTF-8, 'GBK' for GBK, 'GB18030' for GB18030.
        self.TimezoneOffsetFromUTC = '+0800'  # Type 3
        # ---------------------------------------------------------------------

    def _generate_waveform_sequence(self):
        if self._is_12_lead_ecg:
            maximum_waveform_sequences = 5  # PS3.3 A.34.3.4.3 Waveform Sequence
            maximum_waveform_samples = 16384  # PS3.3 A.34.3.4.5 Number of Waveform Samples
        else:
            maximum_waveform_sequences = 4  # PS3.3 A.34.4.4.2 Waveform Sequence
            maximum_waveform_samples = 2 ** 32 - 1  # NumberOfWaveformSamples's VR is `UL`.
        
        data_file_len = fileutil.file_size(self._file)
        pack_size = struct.calcsize(self._format)
        data_file_total_samples = data_file_len // pack_size
        saved_samples = maximum_waveform_sequences * maximum_waveform_samples
        if data_file_total_samples > saved_samples:
            data_file_total_samples = saved_samples

        self._channel_labels = list(self._channel_labels)
        channel_cnt = len(self._channel_labels)
        
        waveform_seq = dicom.sequence.Sequence()
        data_unpacker = unpacker.unpack_data_from_file(self._file, self._format)
        target_fmt = '<{}'.format('h' * channel_cnt)
        
        if self._adjust_callback and hasattr(self._adjust_callback, '__call__'):
            adjusted_data = map(lambda v: map(self._adjust_callback, v), data_unpacker)
        else:
            adjusted_data = data_unpacker

        if self._is_12_lead_ecg:
            assert 1 <= channel_cnt <= 13  # PS3.3 A.34.3.4.4
        else:
            assert 1 <= channel_cnt <= 24  # PS3.3 A.34.4.4.3 Number of Waveform Channels

        assert 200 <= self._sampling_frequency <= 1000 # DICOM PS3.3-2015a A.34.3.4.6
                
        while data_file_total_samples > 0:
            seq_item = dicom.dataset.Dataset()
            seq_item.WaveformOriginality = 'ORIGINAL'  # Type 1
            
            seq_item.NumberOfWaveformChannels = channel_cnt  # Type 1.

            if data_file_total_samples >= maximum_waveform_samples:
                seq_item.NumberOfWaveformSamples = maximum_waveform_samples  # Type 1. UL.
            else:
                seq_item.NumberOfWaveformSamples = data_file_total_samples  # Type 1. UL.
            data_file_total_samples -= seq_item.NumberOfWaveformSamples

            seq_item.SamplingFrequency = '{:d}'.format(self._sampling_frequency)  # Type 1. DS.

            seq_item.ChannelDefinitionSequence = self._generate_channel_definition_sequence()  # Type 1.

            seq_item.WaveformBitsAllocated = 16  # Type 1. PS3.3 C.10.9.1.5 Waveform Bits Allocated and Waveform Sample Interpretation
            seq_item.WaveformSampleInterpretation = 'SS'  # Type 1. PS3.3 A.34.3.4.8 Waveform Sample Interpretation

            # The VR of `Waveform Padding Value` may be OB or OW, so:
            #seq_item.WaveformPaddingValue = b'\x00\x00'
            # will not work, instead:
            seq_item.add_new((0x5400, 0x100A), 'OW', b'\x00\x80')  # Type 1C. OB or OW.

            data = bytearray()
            for i, d in zip(range(seq_item.NumberOfWaveformSamples), adjusted_data):
                data.extend(struct.pack(target_fmt, *d))
            seq_item.add_new((0x5400, 0x1010), 'OW', bytes(data)) # WaveformData. Type 1. OB or OW.

            waveform_seq.append(seq_item)
        
        return waveform_seq

    def _generate_channel_definition_sequence(self):
        channel_def_seq = dicom.sequence.Sequence()

        for label in self._channel_labels:
            channel_def_item = dicom.dataset.Dataset()
            
            channel_def_item.ChannelLabel = label # Type 3. SH.
            channel_def_item.ChannelSourceSequence = self._generate_channel_source_sequence(label) # Type 1
            channel_def_item.ChannelSensitivity = '0.00122' # Type 1C. DS.
            channel_def_item.ChannelSensitivityUnitsSequence = self._generate_channel_sensitivity_units_sequence() # Type 1C
            channel_def_item.ChannelSensitivityCorrectionFactor = '1' # Type 1C. DS. ?
            channel_def_item.ChannelBaseline = '0' # Type 1C. DS.
            channel_def_item.ChannelTimeSkew = '0' # Type 1C. DS. PS3.3 C.10.9.1.4.3 Channel Skew and Channel Offset
            channel_def_item.WaveformBitsStored = 16 # Type 1. US. PS3.3 C.10.9.1.5 Waveform Bits Allocated and Waveform Sample Interpretation

            channel_def_seq.append(channel_def_item)

        return channel_def_seq

    def _generate_channel_source_sequence(self, label):
        # PS3.3 A.34.3.4.7 Channel Source
        # PS3.3 C.10.9.1.4.1 Channel Source and Modifiers
        # PS3.16 CID 3001 ECG Leads
        channel_source_seq = dicom.dataset.Dataset()

        if self._is_12_lead_ecg:
            channel_source_seq.CodeValue = CID_3001_for_12_Lead_ECG[label][0] # Type 1C. SH.
            channel_source_seq.CodingSchemeDesignator = 'MDC' # Type 1C. SH.
            channel_source_seq.CodeMeaning = CID_3001_for_12_Lead_ECG[label][1] # Type 1. LO.
        else:
            pass

        return (channel_source_seq, )

    def _generate_channel_sensitivity_units_sequence(self):
        # I don't how to fill this part, so follow GE's step.
        sensitivity_unit_seq = dicom.dataset.Dataset()
        sensitivity_unit_seq.CodeValue = 'mV' # SH.
        sensitivity_unit_seq.CodingSchemeDesignator = 'UCUM'
        sensitivity_unit_seq.CodingSchemeVersion = '1.4' # Type 1C. SH.
        sensitivity_unit_seq.CodeMeaning = 'millivolt'

        return (sensitivity_unit_seq, )


def ecg_to_dcm(src, dest, extra_ds=dicom.dataset.Dataset(), format_ch='d', callback=None):
    """Convert 12-Lead Electrocardiogram data into DICOM-ECG standard compliant format."""
    # Data values are encoded interleaved. That is:
    # Lead I, II, III, aVR, aVL, aVF, V1, V2, V3, V4, V5, V6, I, II, III, ...
    # The unit of signals collected by the cardiac conduction is: 0.4V/(2^15).
    if not dest:
        dest = fileutil.replace_ext(src, '.dcm')
        
    data_set = ECGDataset(src, '<{}'.format(format_ch * 12), 500,
                          ('I', 'II', 'III', 'aVR', 'aVL', 'aVF', 'V1', 'V2', 'V3', 'V4', 'V5', 'V6'),
                          adjust_callback=callback)
    data_set.update(extra_ds)
    data_set.save_as(dest)


def fecg_to_dcm(src, dest):
    raise NotImplementedError()

