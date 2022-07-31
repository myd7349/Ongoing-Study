#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# yapf -i edfutil.py

# TODO: Allow to export signals into separate files (Even if they have different sample rates).
# TODO: --range
# TODO: print data in Table
# TODO: refine header
# TODO: Read float data
# TODO: Annotation
# TODO: Modify

import argparse
import contextlib
from pathlib import Path
import sys

from EDFlib.edfreader import EDFreader  # pip install EDFlib-Python
import numpy as np  # pip install numpy -i https://pypi.doubanio.com/simple
from rich.console import Console
from rich.table import Table


def get_file_type(edf):
    file_type = edf.getFileType()

    if file_type == edf.EDFLIB_FILETYPE_EDF:
        return 'EDF'
    elif file_type == edf.EDFLIB_FILETYPE_EDFPLUS:
        return 'EDF+'
    elif file_type == edf.EDFLIB_FILETYPE_BDF:
        return 'BDF'
    elif file_type == edf.EDFLIB_FILETYPE_BDFPLUS:
        return 'BDF+'
    else:
        raise ValueError(f'Unsupported EDF file type: {file_type}.')


def dump_header(edf):
    file_type = get_file_type(edf)

    header_table = Table(title=f'{file_type} Header')

    header_table.add_column('Field')
    header_table.add_column('Value')

    if file_type == 'EDF' or file_type == 'BDF':
        header_table.add_row('Patient identification', edf.getPatient())
        header_table.add_row('Recording identification', edf.getRecording())
    else:
        header_table.add_row('Patient code', edf.getPatientCode())
        header_table.add_row('Gender', edf.getPatientGender())
        header_table.add_row('Birthdate', edf.getPatientBirthDate())
        header_table.add_row('Patient name', edf.getPatientName())
        header_table.add_row('Patient additional', edf.getPatientAdditional())
        header_table.add_row('Administration code',
                             edf.getAdministrationCode())
        header_table.add_row('Technician', edf.getTechnician())
        header_table.add_row('Equipment', edf.getEquipment())
        header_table.add_row('Recording additional',
                             edf.getRecordingAdditional())

    header_table.add_row('Reserved', edf.getReserved())
    header_table.add_row('Number of signals', str(edf.getNumSignals()))
    header_table.add_row('Number of data records',
                         str(edf.getNumDataRecords()))
    #header_table.add_row('Data record duration', edf.get)

    console = Console()
    console.print(header_table)

    signal_table = Table(title='Signal Header')

    signal_table.add_column('Signal')
    signal_table.add_column('Sample frequency')
    signal_table.add_column('Transducer')
    signal_table.add_column('Physical dimension')
    signal_table.add_column('Physical minimum')
    signal_table.add_column('Physical maximum')
    signal_table.add_column('Digital minimum')
    signal_table.add_column('Digital maximum')
    signal_table.add_column('Prefilter')
    signal_table.add_column('Samples per datarecord')
    signal_table.add_column('Total samples in file')
    signal_table.add_column('Reserved')

    for signal_number in range(edf.getNumSignals()):
        signal_table.add_row(edf.getSignalLabel(signal_number),
                             str(edf.getSampleFrequency(signal_number)),
                             edf.getTransducer(signal_number),
                             edf.getPhysicalDimension(signal_number),
                             str(edf.getPhysicalMinimum(signal_number)),
                             str(edf.getPhysicalMaximum(signal_number)),
                             str(edf.getDigitalMinimum(signal_number)),
                             str(edf.getDigitalMaximum(signal_number)),
                             edf.getPreFilter(signal_number),
                             str(edf.getSampelsPerDataRecord(signal_number)),
                             str(edf.getTotalSamples(signal_number)),
                             edf.getSignalReserved(signal_number))

    console.print(signal_table)


def canonicalize_label(label):
    return label.strip()


def get_signal_number(edf, label):
    signal_count = edf.getNumSignals()

    for signal_number in range(signal_count):
        signal_label = canonicalize_label(edf.getSignalLabel(signal_number))

        if signal_label == label:
            return signal_number

    raise ValueError(f'Unknown signal label: {label}.')


def check_signal_numbers(edf, signal_numbers, check_sample_rate):
    if not signal_numbers:
        raise ValueError('Signal number(s) or signal label(s) is missing.')

    if len(set(signal_numbers)) < len(signal_numbers):
        raise ValueError('Duplicate signals.')

    signal_count = edf.getNumSignals()

    for signal_number in signal_numbers:
        if signal_number < 0 or signal_number >= signal_count:
            raise ValueError(f'Invalid signal number: {signal_number}.')

    if check_sample_rate:
        samples_per_data_record = edf.getSampelsPerDataRecord(
            signal_numbers[0])

        for signal_number in signal_numbers[1:]:
            samples = edf.getSampelsPerDataRecord(signal_number)
            if samples != samples_per_data_record:
                raise ValueError(
                    f'Signal {signal_number} has different sample rate with signal {signal_numbers[0]}.'
                )


def extract_signals(edf, signal_numbers):
    check_signal_numbers(edf, signal_numbers, True)

    signal_labels = [
        canonicalize_label(edf.getSignalLabel(signal_number))
        for signal_number in signal_numbers
    ]
    print(','.join(signal_labels))

    total_samples = edf.getTotalSamples(signal_numbers[0])
    samples_per_data_record = edf.getSampelsPerDataRecord(signal_numbers[0])

    signal_data = [
        np.empty(samples_per_data_record, dtype=np.int32)
        for signal_number in signal_numbers
    ]

    samples_read = 0

    signal_count = len(signal_numbers)

    while samples_read < total_samples:
        index = 0
        for signal_number in signal_numbers:
            edf.readSamples(signal_number, signal_data[index],
                            samples_per_data_record)
            index += 1

        for i in range(samples_per_data_record):
            for s in range(signal_count - 1):
                print(signal_data[s][i], end=',')
            print(signal_data[signal_count - 1][i])

        samples_read += samples_per_data_record


def nargs_range(nmin, nmax):

    class RequiredLength(argparse.Action):

        def __call__(self, parser, args, values, option_string=None):
            if not nmin <= len(values) <= nmax:
                msg = f'argument \'{self.dest}\' requires between {nmin} and {nmax} arguments.'
                raise argparse.ArgumentTypeError(msg)

            setattr(args, self.dest, values)

    return RequiredLength


def parse_args():
    script_path = Path(sys.argv[0])

    parser = argparse.ArgumentParser(
        prog=script_path.stem,
        description='Extract data from EDF/EDF+/BDF/BDF+ files.',
    )

    parser.add_argument('-i',
                        '--input-file',
                        required=True,
                        help='Input file path')

    parser.add_argument('--header',
                        action='store_true',
                        help='Dump EDF/EDF+ header')

    signal_group = parser.add_mutually_exclusive_group()
    signal_group.add_argument('--all-signals',
                              action='store_true',
                              help='Dump all signals')
    signal_group.add_argument('--signal-number',
                              type=int,
                              nargs='+',
                              help='Specify signal number')
    signal_group.add_argument('--signal-label',
                              nargs='+',
                              help='Specify signal label')

    parser.add_argument('--range',
                        type=int,
                        nargs='+',
                        action=nargs_range(1, 2),
                        help='Specify sample range')

    output_group = parser.add_mutually_exclusive_group()
    output_group.add_argument('--output-file', help='Output file path')
    output_group.add_argument('--output-file-prefix',
                              help='Output file name prefix')

    return parser.parse_args()


def main():
    args = parse_args()

    with contextlib.closing(EDFreader(args.input_file)) as edf:
        if args.header or not args.all_signals and not args.signal_number and not args.signal_label:
            dump_header(edf)

        if args.all_signals:
            extract_signals(edf, tuple(range(edf.getNumSignals())))
        if args.signal_number:
            extract_signals(edf, args.signal_number)
        elif args.signal_label:
            extract_signals(
                edf,
                [get_signal_number(edf, label) for label in args.signal_label])


if __name__ == '__main__':
    main()

# References:
# https://gitlab.com/Teuniz/EDFlib-Python/-/blob/master/examples/test_edfreader.py
# https://rich.readthedocs.io/en/stable/tables.html
# https://docs.python.org/3/library/exceptions.html#bltin-exceptions
# https://www.edfplus.info/
# https://www.edfplus.info/specs/edf.html
# https://www.edfplus.info/specs/edfplus.html
# [python 'with' statement, should I use contextlib.closing?](https://stackoverflow.com/questions/20793283/python-with-statement-should-i-use-contextlib-closing)
# https://docs.python.org/3/library/contextlib.html
# [Require either of two arguments using argparse](https://stackoverflow.com/questions/11154946/require-either-of-two-arguments-using-argparse)
# [Checking if all elements in a list are unique](https://stackoverflow.com/questions/5278122/checking-if-all-elements-in-a-list-are-unique)
