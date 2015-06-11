#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-06-10T17:41+08:00

__author__ = 'myd7349 <myd7349@gmail.com>'
__version__ = '0.0.1'

import argparse
import enum
import sys

import fileutil

class ErrorCode(enum.IntEnum):
    ok = 0
    config_file_not_found = 1
    invalid_config_file = 2
    invalid_option = 3
    ftp_error = 4
    dcmutil_error = 5

_errors = {
    ErrorCode.ok: 'Everything is OK!',
    ErrorCode.config_file_not_found: 'Specified configuration file doesn\'t exist.',
    ErrorCode.invalid_config_file: 'Invalid configuration file.',
    ErrorCode.invalid_option: 'Invalid option.',
    ErrorCode.ftp_error: 'FTP operation failed.',
    ErrorCode.dcmutil_error: 'Operation not completed.',
    }

_prog = fileutil.file_title(sys.argv[0])

_generic_options_group = (
    'Generic',
    (['--config'], {'help': 'configuration file that stores FTP/{} options'.format(_prog)}),
    (['--errcodes'], {'action': 'store_true', 'help': 'list all error codes this program may return'}),
    (['--source'], {'required': True, 'help': 'source data file to be converted'}),
    (['--target'], {'required': True, 'help': 'target DICOM file name'}),
    (['--type'], {'choices': ['ECG', 'FECG'], 'default': 'ECG', 'help': 'source data type: "ECG" for normal 12-Lead ECG, and "FECG" for Foetus ECG'}),
    (['--criteria'], {'help': 'criteria argument'}),
    (['--template'], {'help': 'template file name'}),
    (['-h', '--help'], {'action': 'help', 'help': 'show this help message and exit'}),
    (['-v', '--version'], {'action': 'version', 'version': ' '.join((_prog, __version__, 'by', __author__))}),
    )

_ftp_options_group = (
    'FTP',
    (['--host'], {'help': 'hostname to connect to'}),
    (['--port'], {'help': 'port to connect to'}),
    (['--user'], {'help': 'login user name'}),
    (['--passwd'], {'help': 'login password'}),
    )

_prog_options_group = (
    _prog,
    (['--info'], {'help': 'configuration file that stores additional patient information'}),
    (['--log'], {'help': 'log file name'}),
    )


def _parse_args():
    parser = argparse.ArgumentParser(prog=_prog,
                                     description='Convert input data file to DICOM-ECG standard compliant format.',
                                     epilog='If "--config" is provided, then all FTP/%(prog)s options will be read from this configuration file.\n'
                                     'If "--host" is provided, then target DICOM file will be sent to this host, otherwise \'--target\' stands for a path on local drive.',
                                     formatter_class=argparse.RawDescriptionHelpFormatter,
                                     add_help=False)

    for group in (_generic_options_group, _ftp_options_group, _prog_options_group):
        arg_group = parser.add_argument_group(group[0] + ' options')
        for args, kwargs in group[1:]:
            arg_group.add_argument(*args, **kwargs)

    if len(sys.argv) <= 1:
        parser.print_help()
        _report_error(ErrorCode.ok)
        
    return parser.parse_args()


def _report_error(error_code):
    assert error_code in _errors

    if error_code != ErrorCode.ok:
        print('[{:d}] {}'.format(error_code, _errors[error_code]), file=sys.stderr)
    sys.exit(error_code)


def _load_config(args):
    if not args.config:
        return

    import configparser
    import os.path

    config = configparser.ConfigParser()
    config.optionxform = str

    groups = (_ftp_options_group, _prog_options_group)
    
    if not os.path.exists(args.config):
        # If the configuration file doesn't exist, create it.
        for group in groups:
            config.add_section(group[0])
            for flag, _ in group[1:]:
                config[group[0]][flag[-1][2:]] = ''

        with open(args.config, 'w') as fp:
            config.write(fp)
                
        _report_error(ErrorCode.config_file_not_found)
    else:
        try:
            config.read(args.config)
        except configparser.Error:
            _report_error(ErrorCode.invalid_config_file)


def main():
    args = _parse_args()

    if args.errcodes:
        for code in sorted(_errors):
            print('{:d}: {}'.format(code, _errors[code]))
        _report_error(ErrorCode.ok)

    _load_config(args)


if __name__ == '__main__':
    main()

