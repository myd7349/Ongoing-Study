#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# $ yapf -i bin2txt.py

# TODO: Allow to skip several bytes in each block.

import argparse
import os.path
import sys

import math_eval_v1
import unpacker

# MATLAB: doc fread
known_matlab_types = {
    # Unsigned integers
    'uint': 'I',  # 32 bits
    'uint8': 'B',
    'uint16': 'H',
    'uint32': 'I',
    'uint64': 'Q',
    'uchar': 'B',
    'unsigned char': 'B',
    'ushort': 'H',
    'ulong': None,  # system-dependent
    'ubitn': None,
    # Signed integers
    'int': 'i',
    'int8': 'b',
    'int16': 'h',
    'int32': 'i',
    'int64': 'q',
    'integer*1': 'b',
    'integer*2': 'h',
    'integer*3': 'i',
    'integer*4': 'q',
    'schar': 'b',
    'signed char': 'b',
    'short': 'h',
    'long': None,  # system-dependent
    'bitn': None,
    # Floating-point numbers
    'single': 'f',
    'double': 'd',
    'float': 'f',
    'float32': 'f',
    'float64': 'd',
    'real*4': 'f',
    'real*8': 'd',
    # Characters
    'char*1': None,
    'char': None,
}


def matlab_format_to_struct_format(fmt):
    """Convert MATLAB fread style format to Python struct style format."""
    pass


def is_csv_file(file_path):
    _, file_ext = os.path.splitext(file_path)
    return file_ext.lower() == '.csv'


def is_tsv_file(file_path):
    _, file_ext = os.path.splitext(file_path)
    return file_ext.lower() == '.tsv'


def parse_factor(factor_string):
    """Parse factor string and convert it to a number.
    
    "0.001" -> 0.001
    "1.0/1000" -> 0.001
    """
    try:
        factor = math_eval_v1.aton(factor_string)
        return factor
    except (TypeError, ValueError):
        pass

    try:
        factor = math_eval_v1.math_eval(factor_string)
        return factor
    except:
        pass


def main():
    prog = os.path.splitext(os.path.basename(sys.argv[0]))[0]

    parser = argparse.ArgumentParser(
        prog=prog,
        description='Extract data from binary file.',
    )
    parser.add_argument('-i',
                        '--input-file',
                        required=True,
                        help='Input file path')
    parser.add_argument('--skip-bytes',
                        type=int,
                        default=0,
                        help='Skip how many bytes at the begin of the file')
    parser.add_argument('-f',
                        '--format',
                        required=True,
                        help='Format string to describe the data')
    parser.add_argument('--endian',
                        choices=('little', 'ieee-le', 'le', 'l', 'big',
                                 'ieee-be', 'be', 'b', 'native', 'n'),
                        default='native',
                        help='Endianess of binary data')
    parser.add_argument('-F', '--factor', help='Factor')
    parser.add_argument('-o', '--output-file', help='Output file path')
    parser.add_argument('-d',
                        '--delimiter',
                        help='Column delimiter of output file')
    parser.add_argument('-O',
                        '--overwrite',
                        action='store_true',
                        help='Overwrite existing file')

    args = parser.parse_args()

    if not os.path.isfile(args.input_file):
        sys.stderr.write('Input file \'{0}\' doesn\'t exist!\n'.format(
            args.input_file))
        sys.exit(1)

    if args.skip_bytes < 0:
        sys.stderr.write('Invalid skip bytes: {0}.'.format(args.skip_bytes))
        sys.exit(1)

    # A factor string can be:
    # 1. A numeric literal: "0.001"
    # 2. A math expression: "1.0/1000.0"
    # 3. A math expression with unknown value: "x+300"
    # For 1 and 2, we can get the value of factor via `parse_factor`.
    # For 3, we first replace `x` with `1.0`, and then we call `math_eval`.
    #   If it failed, then it means the factor string is not a valid one.
    #   Otherwise, we evaluate it later.
    if args.factor:
        factor = parse_factor(args.factor)
        if factor is None:
            try:
                _ = math_eval_v1.math_eval(args.factor, x=1)
                fixed_factor = False
            except:
                sys.stderr.write(
                    'Invalid factor: \'{0}\' is neither a valid numeric literal nor a math expression.\n'
                    .format(args.factor))
                sys.exit(1)
        else:
            fixed_factor = True

    if args.output_file and os.path.isfile(
            args.output_file) and not args.overwrite:
        sys.stderr.write('Output file \'{0}\' already exists! '
                         'Please use a different file path or specify '
                         '\'--overwrite\' on the command line.\n'.format(
                             args.output_file))
        sys.exit(1)

    if not args.delimiter:
        if args.output_file:
            if is_csv_file(args.output_file):
                args.delimiter = ','
            elif is_tsv_file(args.output_file):
                args.delimiter = '\t'
            else:
                args.delimiter = ' '
        else:
            args.delimiter = ' '

    if args.output_file:
        output_fp = open(args.output_file, 'w', encoding='ascii')
    else:
        output_fp = sys.stdout

    for line in unpacker.unpack_data_from_file(args.input_file, args.format,
                                               args.skip_bytes):
        if not args.factor:
            output_line = line
        elif fixed_factor:
            output_line = (col * factor for col in line)
        else:
            output_line = (math_eval_v1.math_eval(args.factor, x=col)
                           for col in line)

        output_fp.write(args.delimiter.join(
            (repr(col) for col in output_line)))
        output_fp.write('\n')

    if args.output_file:
        output_fp.close()


if __name__ == '__main__':
    main()

# References:
# [Need Convert Binary file to Txt file](https://stackoverflow.com/questions/5168676/need-convert-binary-file-to-txt-file)
# [python float to string without precision loss](https://stackoverflow.com/questions/38055000/python-float-to-string-without-precision-loss)
# [How to make a short and long version of a required argument using Python Argparse?](https://stackoverflow.com/questions/28638813/how-to-make-a-short-and-long-version-of-a-required-argument-using-python-argpars)
# https://numpy.org/doc/stable/reference/generated/numpy.fromfile.html
