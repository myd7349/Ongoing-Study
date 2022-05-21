# -*- coding: utf-8 -*-
# Usage(In Spyder):
# runfile('D:/dump_edf.py', args='-i E:\eeg.edf --signal 28 --range 0 2000 --plot', wdir='E:')

import argparse
from collections import OrderedDict
import os.path
import struct
import sys
import time

try:
    import matplotlib.pyplot as plt
    can_plot = True
except ImportError:
    can_plot = False

import tabulate  # pip install tabulate


def get_prog():
    return os.path.splitext(os.path.basename(sys.argv[0]))[0]


def perror(*args, **kwargs):
    print(*args, **kwargs, file=sys.stderr)


def chunks(lst, n):
    """Yield successive n-sized chunks from lst."""
    for i in range(0, len(lst), n):
        yield lst[i:i + n]


def n_chunks(lst, n):
    """Yield successive n chunks from lst."""
    assert len(lst) % n == 0

    chunk_size = len(lst) // n

    for i in range(0, len(lst), chunk_size):
        yield lst[i:i + chunk_size]


def I(data):
    return int(data.rstrip())


def F(data):
    return float(data.rstrip())


def X(data):
    return data if data != b'X' else None


def nargs_range(nmin, nmax):
    class RequiredLength(argparse.Action):
        def __call__(self, parser, args, values, option_string=None):
            if not nmin <= len(values) <= nmax:
                msg = f'argument \'{self.dest}\' requires between {nmin} and {nmax} arguments.'
                raise argparse.ArgumentTypeError(msg)

            setattr(args, self.dest, values)

    return RequiredLength


def main():
    parser = argparse.ArgumentParser(
        prog=get_prog(),
        description='Dump informations in EDF/EDF+ files.',
    )
    parser.add_argument('-i',
                        '--input-file',
                        required=True,
                        help='Input file path')
    parser.add_argument('--edfplus',
                        action='store_true',
                        help='Parse as EDF+ file')
    parser.add_argument('--header',
                        action='store_true',
                        help='Dump EDF/EDF+ headers')
    parser.add_argument('--signal',
                        type=int,
                        help='Dump signal')
    parser.add_argument('--range',
                        type=int,
                        nargs='+',
                        action=nargs_range(1, 2),
                        help='Dump sample range')
    parser.add_argument('--scale',
                        action='store_true',
                        help='Convert raw AD data to physical data')
    parser.add_argument('--plot',
                        action='store_true',
                        help='Plot samples with matplotlib')

    args = parser.parse_args()

    if not os.path.isfile(args.input_file):
        perror(f'Input file \'{args.input_file}\' doesn\'t exist!')
        sys.exit(1)

    if not args.header and args.signal is None:
        args.header = True

    if args.signal is None and args.plot:
        perror('--signal parameter is missing.')
        sys.exit(1)

    if args.plot and not can_plot:
        perror('matplotlib is required for plotting.')
        sys.exit(1)

    file = open(args.input_file, 'rb')

    # First 256 bytes of the header record
    first_256_bytes = file.read(256)

    version        = first_256_bytes[0:8]           # 8 ascii : version of this data format (0)
    patient_info   = first_256_bytes[8:8 + 80]      # 80 ascii : local patient identification
    record_info    = first_256_bytes[88:88 + 80]    # 80 ascii : local recording identification
    start_date     = first_256_bytes[168:168 + 8]   # 8 ascii : startdate of recording (dd.mm.yy)
    start_time     = first_256_bytes[176:176 + 8]   # 8 ascii : starttime of recording (hh.mm.ss)
    header_bytes   = first_256_bytes[184:184 + 8]   # 8 ascii : number of bytes in header record
    reserved       = first_256_bytes[192:192 + 44]  # 44 ascii : reserved
    n_data_records = first_256_bytes[236:236 + 8]   # 8 ascii : number of data records (-1 if unknown)
    duration       = first_256_bytes[244:244 + 8]   # 8 ascii : duration of a data record, in seconds
    ns             = first_256_bytes[252:252 + 4]   # 4 ascii : number of signals (ns) in data record

    is_edfplus = reserved.startswith(b'EDF+')

    if args.header:
        print('Is EDF+?', is_edfplus)
        print('Version:', version)
        print('Patient:', patient_info)
        print('Record:', record_info)
        print('Start date(dd.mm.yy):', start_date)
        print('Start time(hh.mm.ss):', start_time)
        print('Header bytes:', header_bytes)
        print('Reserved:', reserved)
        print('Number of data records:', n_data_records)
        print('Duration(secs):', duration)
        print('Number of signals:', ns)

        #if is_edfplus and args.edfplus:
        if args.edfplus:
            print('-------------------- EDF+ header begin --------------------')
            # Patient
            patient_fields = patient_info.split()

            print('Patient:')
            print('\tID:', X(patient_fields[0]))
            print('\tSex:', X(patient_fields[1]))
            print('\tDOB(dd-MMM-yyyy):', X(patient_fields[2]))
            print('\tName:', X(patient_fields[3]))
            print('\tAdditional:', patient_fields[4:])

            # Local recording identification
            record_fields = record_info.split()
            assert record_fields[0] == b'Startdate'

            print('Local recording identification:')
            print('\tStartdate(dd-MMM-yyyy):', X(record_fields[1]))
            print('\tEEG/PSG number:', X(record_fields[2]))
            print('\tInvestigator/Technician:', X(record_fields[3]))
            print('\tEquipment assigned code:', X(record_fields[4]))
            print('\tAdditional:', record_fields[5:])

            # Start date & time
            start_year_ascii = start_date[6:8]
            if start_year_ascii == 'yy':
                raise NotImplementedError("")
            else:
                start_year_int = int(start_year_ascii)
                if 0 <= start_year_int <= 84:
                    start_year_int += 2000
                elif 85 <= start_year_int <= 99:
                    start_year_int += 1900

            start_datetime_ascii = start_date[0:6].decode('ascii') + \
                                   str(start_year_int) + \
                                   ' ' + \
                                   start_time.decode('ascii')
            start_datetime = time.strptime(start_datetime_ascii, '%d.%m.%Y %H.%M.%S')

            start_datetime_str = time.strftime('%Y-%m-%d %H:%M:%S', start_datetime)
            print('Start datetime:', start_datetime_str)

            # Reserved
            print('Reserved:')
            print('\tFirst five bytes:', reserved[0:5])
            print('\tIs contiguous?', reserved[0:5] != b'EDF+D')
            print('-------------------- EDF+ header end ----------------------')

    number_of_signals = I(ns)
    
    # ns * 16 ascii : ns * label (e.g. EEG Fpz-Cz or Body temp)
    labels = file.read(number_of_signals * 16)
    # ns * 80 ascii : ns * transducer type (e.g. AgAgCl electrode)
    transducer_types = file.read(number_of_signals * 80)
    # ns * 8 ascii : ns * physical dimension (e.g. uV or degreeC)
    units = file.read(number_of_signals * 8)
    # ns * 8 ascii : ns * physical minimum (e.g. -500 or 34)
    physical_minimums = file.read(number_of_signals * 8)
    # ns * 8 ascii : ns * physical maximum (e.g. 500 or 40)
    physical_maximums = file.read(number_of_signals * 8)
    # ns * 8 ascii : ns * digital minimum (e.g. -2048)
    digital_minimums = file.read(number_of_signals * 8)
    # ns * 8 ascii : ns * digital maximum (e.g. 2047)
    digital_maximums = file.read(number_of_signals * 8)
    # ns * 80 ascii : ns * prefiltering (e.g. HP:0.1Hz LP:75Hz)
    prefilterings = file.read(number_of_signals * 80)
    # ns * 8 ascii : ns * nr of samples in each data record
    number_of_samples = file.read(number_of_signals * 8)
    # ns * 32 ascii : ns * reserved
    _ = file.read(number_of_signals * 32)

    header_bytes_int = I(header_bytes)
    assert header_bytes_int == 256 + number_of_signals * 256

    if args.header:
        def S(data):
            return tuple(x.rstrip() for x in n_chunks(data, number_of_signals))

        # Make it a table
        headers = 'Label', 'Transducer', 'Physical Dimension', 'Physical Min', \
            'Physical Max', 'Digital Min', 'Digital Max', 'Prefiltering', 'Samples'
        columns = S(labels), S(transducer_types), S(units), S(physical_minimums), \
            S(physical_maximums), S(digital_minimums), S(digital_maximums), S(prefilterings), S(number_of_samples)
        assert len(headers) == len(columns)
        table = OrderedDict(zip(headers, columns))
        print(tabulate.tabulate(table, headers='keys', showindex='always'))

    if not args.signal is None:
        if args.signal < 0 or args.signal >= number_of_signals:
            perror(f'Signal number {args.signal} is not in range [0, {number_of_signals}).')
            sys.exit(1)

        number_of_data_records = I(n_data_records)
        number_of_samples_ints = tuple(I(x) for x in n_chunks(number_of_samples, number_of_signals))
        data_record_size_in_bytes = sum(number_of_samples_ints) * 2

        sample_range_begin = 0
        sample_range_end = number_of_data_records * number_of_samples_ints[args.signal]
        if args.range:
            sample_range_begin = max(sample_range_begin, args.range[0])
            if len(args.range) == 2:
                sample_range_end = min(sample_range_end, args.range[1])

        if args.header:
            print('Each data record size(bytes):', data_record_size_in_bytes)

        #physical_minimums_ints = tuple(I(x) for x in n_chunks(physical_minimums, number_of_signals))
        #physical_maximums_ints = tuple(I(x) for x in n_chunks(physical_maximums, number_of_signals))
        #digital_minimums_ints = tuple(I(x) for x in n_chunks(digital_minimums, number_of_signals))
        #digital_maximums_ints = tuple(I(x) for x in n_chunks(digital_maximums, number_of_signals))
        physical_minimums_ints = tuple(F(x) for x in n_chunks(physical_minimums, number_of_signals))
        physical_maximums_ints = tuple(F(x) for x in n_chunks(physical_maximums, number_of_signals))
        digital_minimums_ints = tuple(F(x) for x in n_chunks(digital_minimums, number_of_signals))
        digital_maximums_ints = tuple(F(x) for x in n_chunks(digital_maximums, number_of_signals))
        scale_lambdas = tuple(lambda x: (pmax - pmin) / (dmax - dmin) * x
                              for pmax, pmin, dmax, dmin in zip(physical_maximums_ints,
                                                               physical_minimums_ints,
                                                               digital_maximums_ints,
                                                               digital_minimums_ints))

        def iter_signal_samples(signal, begin, end, scale):
            sample_no = 0

            for i in range(number_of_data_records):
                data_record_offset_in_bytes = header_bytes_int + i * data_record_size_in_bytes
                signal_offset = sum(number_of_samples_ints[0:signal]) * 2

                file.seek(data_record_offset_in_bytes + signal_offset)
                signal_data_in_current_record = file.read(number_of_samples_ints[signal] * 2)
                signal_samples = struct.iter_unpack('<h', signal_data_in_current_record)

                for sample in signal_samples:
                    if sample_no < begin:
                        sample_no += 1
                        continue
                    elif sample_no >= end:
                        break

                    if not scale:
                        yield sample[0]
                    else:
                        yield scale_lambdas[signal](sample[0])

                    sample_no += 1

        for sample in iter_signal_samples(args.signal, sample_range_begin, sample_range_end, args.scale):
            print(sample, end=None)

        if args.plot:
            x = range(sample_range_begin, sample_range_end)
            y = tuple(iter_signal_samples(args.signal, sample_range_begin, sample_range_end, args.scale))
            fig, ax = plt.subplots()
            ax.plot(x, y)


if __name__ == '__main__':
    main()


# References:
# https://www.edfplus.info/specs/edf.html
# https://www.edfplus.info/specs/edfplus.html
# [How do I split a list into equally-sized chunks?](https://stackoverflow.com/questions/312443/how-do-i-split-a-list-into-equally-sized-chunks)
# [How can I make a dictionary from separate lists of keys and values?](https://stackoverflow.com/questions/209840/how-can-i-make-a-dictionary-from-separate-lists-of-keys-and-values)
# [Reading integers from binary file in Python](https://stackoverflow.com/questions/1163459/reading-integers-from-binary-file-in-python)
# [Python argparse: Is there a way to specify a range in nargs?](https://stackoverflow.com/questions/4194948/python-argparse-is-there-a-way-to-specify-a-range-in-nargs)
# https://matplotlib.org/stable/tutorials/introductory/usage.html
# https://github.com/Slion/SharpLibEuropeanDataFormat/blob/50e59b1467a98dde4445dddc5a6fcde15829288c/Project/Lib/EDF/BaseSignal.cs#L56
# > public double ScaledSample(int aIndex) { return Samples[aIndex] * ScaleFactor(); }
# >
# > public double ScaleFactor() { return (PhysicalMaximum.Value - PhysicalMinimum.Value)/(DigitalMaximum.Value - DigitalMinimum.Value); }
# https://gitlab.com/Teuniz/EDFlib
# > units per bit = (physical max - physical min) / (digital max - digital min)
# > offset = (physical max / units per bit) - digital max
