#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-06-10T17:41+08:00

__author__ = 'myd7349 <myd7349@gmail.com>'
__version__ = '0.0.2'

import argparse
import enum
import os
import sys

import fileutil


class _ErrorCode(enum.IntEnum):
    ok = 0
    config_file_not_found = 1
    invalid_config_file = 2
    invalid_option = 3
    ftp_error = 4
    source_file_not_found = 5
    convert_operation_failed = 6
    not_implemented = 7

_errors = {
    _ErrorCode.ok: 'Everything is OK!',
    _ErrorCode.config_file_not_found: 'Specified configuration file doesn\'t exist.',
    _ErrorCode.invalid_config_file: 'Invalid configuration file.',
    _ErrorCode.invalid_option: 'Invalid option.',
    _ErrorCode.ftp_error: 'FTP operation failed.',
    _ErrorCode.source_file_not_found: 'Source file doesn\'t exist.',
    _ErrorCode.convert_operation_failed: 'Operation failed.',
    _ErrorCode.not_implemented: 'Not implemented.',
    }

class _ListErrorCodesAction(argparse.Action):
    def __init__(self, option_strings, dest=argparse.SUPPRESS, default=argparse.SUPPRESS, help=None):
        super().__init__(option_strings=option_strings, dest=dest, default=default, nargs=0, help=help)

    def __call__(self, parser, namespace, values, option_string=None):
        for code in sorted(_errors):
            print('{:d}: {}'.format(code, _errors[code]))
        _report_error(_ErrorCode.ok)

_prog = fileutil.file_title(sys.argv[0])

_generic_options_group = (
    'Generic',
    (['--callback'], {'help': 'callback function used to adjust the unpacked data'}),
    (['--config'], {'help': 'configuration file that stores FTP/{} options'.format(_prog)}),
    (['--criteria'], {'help': 'criteria argument'}),
    (['--errors'], {'action': _ListErrorCodesAction, 'help': 'list all error codes this program may return'}),
    (['--format'], {'choices': list('hHiIfd'), 'default': 'd',
                    'help': 'format characters used by unpacker when unpacking data from file'}),
    (['--source'], {'required': True, 'help': 'source data file to be converted'}),
    (['--target'], {'help': 'target DICOM file name'}),
    (['--template'], {'help': 'template file name'}),
    (['--type'], {'choices': ['ECG', 'FECG'], 'default': 'ECG',
                  'help': 'source data type: "ECG" for normal 12-Lead ECG, and "FECG" for Foetus ECG'}),
    (['--srcfmt'], {'choices': ['RAW', 'SCP-ECG', 'HL7-aECG', 'DICOM-ECG'],
                    'default': 'RAW', 'help': 'source file format'}),
    (['--dstfmt'], {'choices': ['RAW', 'SCP-ECG', 'HL7-aECG', 'DICOM-ECG'],
                    'default': 'DICOM-ECG', 'help': 'destination file format'}),
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
    parser = argparse.ArgumentParser(
        prog=_prog,
        description='Convert input data file to DICOM-ECG standard compliant format.',
        epilog='If "--config" is provided, then all FTP/%(prog)s options will be read from this configuration file.\n'
               'If "--host" is provided, then target DICOM file will be sent to this host, otherwise \'--target\' '
               'stands for a path on local drive.',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        add_help=False)

    for group in (_generic_options_group, _ftp_options_group, _prog_options_group):
        arg_group = parser.add_argument_group(group[0] + ' options')
        for args, kwargs in group[1:]:
            arg_group.add_argument(*args, **kwargs)

    if len(sys.argv) <= 1:
        # parser.print_help(); _report_error(_ErrorCode.ok)
        sys.argv.append('-h')
        
    return parser.parse_args()


def _report_error(error_code):
    assert error_code in _errors

    if error_code != _ErrorCode.ok:
        print('[{:d}] {}'.format(error_code, _errors[error_code]), file=sys.stderr)

    sys.exit(error_code)


def _load_config(args):
    assert isinstance(args, argparse.Namespace) and hasattr(args, 'config')
    
    if not args.config:
        return

    import configparser

    config = configparser.ConfigParser()
    config.optionxform = str

    groups = (_ftp_options_group, _prog_options_group)
    
    if not os.path.exists(args.config):
        # If the configuration file doesn't exist, create it.
        for group in groups:
            config.add_section(group[0])
            for flag, _ in group[1:]:
                dest = flag[-1][2:]
                value = getattr(args, dest, '')
                config[group[0]][dest] = value if value else ''

        with open(args.config, 'w') as fp:
            config.write(fp)
                
        _report_error(_ErrorCode.config_file_not_found)
    else:
        try:
            config.read(args.config)

            for option, value in ((option, config[section][option])
                                  for section in config for option in config[section]):
                if value and not getattr(args, option, True):
                    setattr(args, option, value)
        except configparser.Error:
            _report_error(_ErrorCode.invalid_config_file)


def _get_logger(args):
    assert isinstance(args, argparse.Namespace) and hasattr(args, 'log')

    import logging

    log_file = args.log if args.log else os.path.join(os.path.expanduser('~'), _prog + '.log')
    logging.basicConfig(level=logging.NOTSET, filename=log_file,
                        format='%(asctime)s %(name)s [%(levelname)s]: %(message)s')
    return logging.getLogger(_prog)


def main():
    args = _parse_args()

    _load_config(args)
    logger = _get_logger(args)

    if not args.source or not os.path.isfile(args.source):
        logger.error('Invalid source file: {}'.format(args.source))
        _report_error(_ErrorCode.source_file_not_found)

    if not args.target:
        args.target = fileutil.replace_ext(args.source, '.dcm')

    import tempfile
    if args.host:
        fd, dest_dcm = tempfile.mkstemp(); os.close(fd)
    else:
        dest_dcm = args.target

    import dat2dcm_v2
    from PatientInfoProvider import fetch_patient_info
    try:
        extra_ds = {}
        if args.info:
            extra_ds = fetch_patient_info(args.info, criteria_arg=args.criteria)
        dat2dcm_v2.ecg_to_dcm(args.source, dest_dcm, extra_ds, args.format)
        logger.info('{} -> {}'.format(args.source, dest_dcm))
    except Exception as exc:
        logger.info('Failed to complete this operation: {} -> {}. {!r}'.format(args.source, dest_dcm, exc))
        raise

    if args.host:
        import ftplib

        try:
            with ftplib.FTP() as ftp:
                ftp.connect(args.host, int(args.port, 0) if args.port else 0)
                ftp.login(args.user, args.passwd)
                args.target = os.path.basename(args.target)
                with open(dest_dcm, 'rb') as fp:
                    ftp.storbinary('STOR {}'.format(args.target), fp)
                logger.info('The target file is saved as: {}'.format(args.target))
        except (ftplib.Error, OSError) as e:
            logger.error('{!r}'.format(e))
            _report_error(_ErrorCode.ftp_error)
        finally:
            os.unlink(dest_dcm)


if __name__ == '__main__':
    main()
