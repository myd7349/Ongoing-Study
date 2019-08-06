#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import os.path
import re
import string
import sys

import xlwt


def iter_file(path):
    for root, dirs, files in os.walk(path):
        for file in files:
            yield os.path.join(root, file)


def try_open_file(file, encoding):
    try:
        with open(file, 'r', encoding=encoding) as fp:
            fp.read()
        return True
    except Exception as e:
        return False


def get_file_ext(file):
    return os.path.splitext(file)[1]


def get_file_encoding(file):
    known_encodings = (
        'ascii',
        'utf-8',
        'utf-8-sig',
        'utf-16',
        'utf-16-le',
        'utf-16-be',
        'utf-32',
        'utf-32-le',
        'utf-32-be',
        'big5',
        'big5hkscs',
        'euc_jp',
        'gb18030',
        'gb2321',
        'gbk',
        )
    for encoding in known_encodings:
        if try_open_file(file, encoding):
            return encoding


source_file_extensions = frozenset(
    (
        '.c',
        '.cpp',
        '.h',
        'hpp',
        '.cxx',
        '.rc',
        '.cs',
    )
)


def iter_source_files():
    for path in sys.argv[1:]:
        for file in iter_file(path):
            ext = get_file_ext(file).lower()
            if ext in source_file_extensions:
                yield file


directives_re = r'^[ \t"]*#[ \t]*(?:include|import|pragma|error)[ \t]*'
string_re = r'[^"\\]*"([^"\\]*)"'


def is_ascii_string(s):
    for ch in s:
        if ch not in string.printable:
            return False
    
    return True


def main():
    line_no = 1

    workbook = xlwt.Workbook()
    sheet = workbook.add_sheet('Strings')

    style = xlwt.easyxf('font: name Times New Roman, color-index black, bold on')

    sheet.write(0, 0, 'ID', style)
    sheet.write(0, 1, 'File Name', style)
    sheet.write(0, 2, 'Line No.', style)
    sheet.write(0, 3, 'Text', style)

    for file in iter_source_files():
        encoding = get_file_encoding(file)
        if encoding:
            with open(file, 'r', encoding=encoding) as fp:
                infile_line_no = 0

                for line in fp:
                    infile_line_no += 1

                    if re.search(directives_re, line):
                        continue

                    strings = re.findall(string_re, line)
                    if not strings:
                        continue

                    if all((is_ascii_string(s) for s in strings)):
                        continue

                    line = line.strip(' \t')
                    out_line = f'{line_no}\t{os.path.basename(file)}\t{infile_line_no}\t{line}'
                        
                    sheet.write(line_no, 0, line_no)
                    sheet.write(line_no, 1, os.path.basename(file))
                    sheet.write(line_no, 2, infile_line_no)
                    sheet.write(line_no, 3, line)

                    print(out_line, end='')

                    line_no += 1
        else:
            print("Trying to open {0} with encoding {1} failed.".format(file, encoding))

    workbook.save('strings.xls')


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print(f"Usage:\n  {os.path.basename(__file__)} <dir>...")
    else:
        main()
