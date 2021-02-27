#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Formated with `yapf` using pep8 style:
# https://yapf.now.sh/
# https://github.com/google/yapf
# http://pep8online.com/
# autopep8
# $ yapf -i extract_columns.py

import argparse
import os.path
import re
import sys


def enumerate_lines_from_file(input_file, encoding=None, header_lines=0):
    with open(input_file, mode='r', encoding=encoding) as fp:
        current_line_no = 0
        for line in fp:
            if current_line_no >= header_lines:
                yield line

            current_line_no += 1


def enumerate_lines_from_stdin(header_lines=0):
    current_line_no = 0
    run = True

    while run:
        try:
            line = input()

            if current_line_no >= header_lines and line:
                yield line

            current_line_no += 1
        except (EOFError, KeyboardInterrupt):
            #raise StopIteration
            run = False


def extract_columns(lines, columns, delimiter=None, use_regexp=False):
    total_columns = -1

    for line in lines:
        line = line.strip()

        if use_regexp:
            line_fields = re.split(delimiter, line)
        else:
            line_fields = line.split(delimiter)

        if total_columns == -1:
            total_columns = len(line_fields)
            if columns is None:
                columns = tuple(range(0, total_columns))

            for column_no in columns:
                if column_no < 0 or column_no >= total_columns:
                    raise RuntimeError(
                        'Unexpected column number: {0}. Total columns: {1}'.
                        format(column_no, total_columns))
        elif len(line_fields
                 ) < total_columns:  # Use '!=' here to enable strict mode.
            raise RuntimeError(
                'Unexpected line format: {0}. Expected columns: {1}'.format(
                    line, total_columns))

        yield tuple((line_fields[c] for c in columns))


def is_csv_file(file_path):
    _, file_ext = os.path.splitext(file_path)
    return file_ext.lower() == '.csv'


def main():
    prog = os.path.splitext(os.path.basename(sys.argv[0]))[0]

    parser = argparse.ArgumentParser(
        prog=prog,
        description='Extract specified columns of data from a text file.',
    )
    parser.add_argument('-i', '--input-file', help='Input file path')
    parser.add_argument('--encoding', help='Input/Output file encoding')
    parser.add_argument('--header-lines',
                        type=int,
                        default=0,
                        help='Count of header lines to skip')
    parser.add_argument('-d', '--delimiter', help='Column delimiter')
    parser.add_argument('--use-regexp',
                        action='store_true',
                        help='Colum delimiter is a regular expression')
    parser.add_argument('-c',
                        '--columns',
                        nargs='+',
                        type=int,
                        help='Column numbers (0 based)')
    parser.add_argument('-o', '--output-file', help='Output file path')
    parser.add_argument('-O',
                        '--overwrite',
                        action='store_true',
                        help='Overwrite existing file')
    parser.add_argument('--output-delimiter',
                        default=' ',
                        help='Column delimiter of output file')

    args = parser.parse_args()

    if args.input_file and not os.path.isfile(args.input_file):
        sys.stderr.write('Input file \'{0}\' doesn\'t exist!\n'.format(
            args.input_file))
        sys.exit(1)

    if not args.encoding:
        args.encoding = sys.getdefaultencoding()

    if args.header_lines < 0:
        sys.stderr.write('Invalid header lines: {0}.'.format(
            args.header_lines))
        sys.exit(1)

    is_input_csv = args.input_file and is_csv_file(args.input_file)

    if args.use_regexp and not args.delimiter:
        sys.stderr.write(
            'Delimiter is not a valid regular expression: {0}.'.format(
                args.delimiter))
        sys.exit(1)
    elif not args.delimiter and not args.use_regexp:
        # .txt and .csv are most commonly used data formats.
        args.use_regexp = True

        if is_input_csv:
            # r'(\s+)|(\s*[,]\s*)' is problematic for columns seperated by spaces.
            # r'\s+' is somewhat ok. But, re.split(r'\s+', 'a b c\n') returns:
            # ['a', 'b', 'c', '']
            args.delimiter = r'\s*[,]\s*'
        else:
            args.delimiter = r'\s+'

    if args.output_file and os.path.isfile(
            args.output_file) and not args.overwrite:
        sys.stderr.write('Output file \'{0}\' already exists! '
                         'Please use a different file path or specify '
                         '\'--overwrite\' on the command line.\n'.format(
                             args.output_file))
        sys.exit(1)

    if not args.output_delimiter:
        if not args.use_regexp:
            args.output_delimiter = args.delimiter

        if not args.output_delimiter:
            args.output_delimiter = ',' if is_input_csv else ' '

    if args.output_file:
        output_fp = open(args.output_file, 'w', encoding=args.encoding)
    else:
        output_fp = sys.stdout

    if args.input_file is None:
        lines = enumerate_lines_from_stdin(header_lines=args.header_lines)
    else:
        lines = enumerate_lines(args.input_file,
                                encoding=args.encoding,
                                header_lines=args.header_lines)
    for extracted_columns in extract_columns(lines, args.columns,
                                             args.delimiter, args.use_regexp):
        output_fp.write(args.output_delimiter.join(extracted_columns))
        output_fp.write('\n')

    if args.output_file:
        output_fp.close()


if __name__ == '__main__':
    main()

# References:
# [How to parse on/off (debug) flag using argparse?](https://stackoverflow.com/questions/13415400/how-to-parse-on-off-debug-flag-using-argparse)
# [How do you find out what the "system default encoding" is?](https://stackoverflow.com/questions/7387744/how-do-you-find-out-what-the-system-default-encoding-is)
# [How can I pass a list as a command-line argument with argparse?](https://stackoverflow.com/questions/15753701/how-can-i-pass-a-list-as-a-command-line-argument-with-argparse)
# [Python: filtering lists by indices](https://stackoverflow.com/questions/11847491/python-filtering-lists-by-indices)
# [Extracting extension from filename in Python](https://stackoverflow.com/questions/541390/extracting-extension-from-filename-in-python)
# [Why are empty strings returned in split() results?](https://stackoverflow.com/questions/2197451/why-are-empty-strings-returned-in-split-results)
# [Python regex split without empty string](Python regex split without empty string)
