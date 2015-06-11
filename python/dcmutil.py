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
_generic_options = (
    {'dest': '--config', 'help': 'configuration file that stores FTP/{} options'.format(_prog)}
    )

def _parse_args():
    parser = argparse.ArgumentParser(prog=_prog,
                                     description='Convert input data file to DICOM-ECG standard compliant format.',
                                     epilog='If "--config" is provided, then all FTP/%(prog)s options will be read from this configuration file.\n'
                                     'If "--host" is provided, then target DICOM file will be sent to this host, otherwise \'--target\' stands for a path on local drive.',
                                     formatter_class=argparse.RawDescriptionHelpFormatter,
                                     add_help=False)
    
    generic_options = parser.add_argument_group('Generic options')
    generic_options.add_argument(dest='--config', help='configuration file that stores FTP/{} options'.format(parser.prog))
    generic_options.add_argument('-h', '--help', action='help', help='show this help message and exit')
    generic_options.add_argument('-v', '--version', action='version', version=' '.join((fileutil.file_title('%(prog)s'), __version__, 'by', __author__)))

    ftp_options = parser.add_argument_group('FTP options')
    ftp_options.add_argument('--host', default='', help='hostname to connect to')
    ftp_options.add_argument('--port', default='', help='port to connect to')
    ftp_options.add_argument('--user', default = '', help='login user name')
    ftp_options.add_argument('--passwd', default = '', help='login password')

    dcmutil_options = parser.add_argument_group(parser.prog + ' options')
    dcmutil_options.add_argument('--source', required=True, help='source data file to be converted')
    dcmutil_options.add_argument('--target', required=True, help='target DICOM file name')
    dcmutil_options.add_argument('--type', choices=['ECG', 'FECG'], help='source data type: "ECG" for normal 12-Lead ECG, and "FECG" for Foetus ECG')
    
    dcmutil_options.add_argument('--template', help='template file name')
    dcmutil_options.add_argument('--info', help='configuration file that stores additional patient information')
    dcmutil_options.add_argument('--criteria', help='criteria argument')
    dcmutil_options.add_argument('--log', help='log file name')
    dcmutil_options.add_argument('--errcodes', action='store_true', help='list all error codes this program may return')

    if len(sys.argv) <= 1:
        parser.print_help()
        _report_error(ErrorCode.ok)
        
    return parser.parse_args()

def _report_error(error_code):
    assert error_code in _errors

    if error_code != ErrorCode.ok:
        print('[{:d}] {}'.format(error_code, _errors[error_code]), file=sys.stderr)
    sys.exit(error_code)

def main():
    import configparser
    import os.path
    
    args = _parse_args()

    if args.errcodes:
        for code in sorted(_errors):
            print('{:d}: {}'.format(code, _errors[code]))
        _report_error(ErrorCode.ok)

    if args.config:
        config = configparser.ConfigParser()
        
        if not os.path.exists(args.config):
            _report_error(ErrorCode.config_file_not_found)
        else:
            try:
                config.read(args.config)
            except configparser.Error as e:
                _report_error(ErrorCode.invalid_config_file)


if __name__ == '__main__':
    main()

