# -*- coding: utf-8 -*-

# 2016-10-20T16:00+08:00


import fnmatch
import glob
import itertools
import os
import re
import subprocess
import sys

import fileutil


# Match version numbers of these formats:
# 1.2.3
# 1.2.3.4
version_number_re = r'([0-9]+(?:.[0-9]+){2,3})'

# Match version numbers of this format:
incomplete_version_number_re = r'^[0-9]+(?:.[0-9]+){2}$'

# Match a line, in Changelog.txt, which contains a valid version number
version_line_re = r'^### v{0}.*$'.format(version_number_re)


def get_topmost_version_line(changelog_file):
    with open(changelog_file, 'r', encoding=fileutil.get_file_encoding(changelog_file, 'utf-8')) as fp:
        return next(filter(lambda line: re.match(version_line_re, line), fp.readlines()))


def get_version_number(version_line):
    match_res = re.match(version_line_re, version_line)
    assert match_res, 'Invalid version line'
    if match_res:
        return match_res.groups()[0]


# 1.2.3 -> 1.2.3.0
def canonicalize_version_number(version_number):
    assert re.match(r'^{0}$'.format(version_number_re), version_number), 'Invalid version number format(neither x.x.x nor x.x.x.x)'
    if re.match(incomplete_version_number_re, version_number):
        version_number += '.0'
    return version_number


def perror(*args, **kwargs):
    sys.stderr.write(*args, **kwargs)
    sys.exit(1)


def quote_path(path):
    if path.startswith('"') and path.endswith('"'):
        return path
    return '"{0}"'.format(path)


def is_dll_or_exe(file):
    assert os.path.isfile(file)
    return fnmatch.fnmatch(file, '*.dll') or fnmatch.fnmatch(file, '*.exe')

    
def _get_full_path(candidate_path, file_name):
    if candidate_path is None:
        candidate_path = ''

    if os.path.isfile(candidate_path):
        return candidate_path
    elif os.path.isdir(candidate_path):
        return os.path.join(candidate_path, file_name)
    else:
        return os.path.join(os.path.dirname(sys.argv[0]), file_name)


def _iterate_module_files_legacy(module_path):
    assert os.path.isdir(module_path)
    yield from filter(is_dll_or_exe,
                      map(lambda item: os.path.join(module_path, item),
                          os.listdir(module_path)))


def _iterate_module_files_new(module_path):
    assert os.path.isdir(module_path)
    yield from filter(is_dll_or_exe,
                      filter(os.path.isfile,
                             map(lambda item_name: os.path.join(module_path, item_name),
                                 map(lambda item: item.name,
                                     os.scandir(module_path)))))


# `os.scandir` is new in Python 3.5, and Python 3.5 needs Windows Vista or higher. 
if sys.version_info >= (3, 5):
    iterate_module_files_v1 = _iterate_module_files_new
    run_subprocess = subprocess.run
else:
    iterate_module_files_v1 = _iterate_module_files_legacy
    run_subprocess = subprocess.call


_module_patterns = '*.dll', '*.exe'


def iterate_module_files_v2(module_path):
    assert os.path.isdir(module_path)

    for pattern in _module_patterns:
        pattern = os.path.join(module_path, pattern)
        yield from glob.iglob(pattern)


def iterate_module_files_v3(module_path):
    assert os.path.isdir(module_path)

    yield from itertools.chain.from_iterable(
        glob.iglob(pattern) for pattern in map(lambda pattern: os.path.join(module_path, pattern), _module_patterns))


def main():
    """
    Usage:
      SetPEVersion.py (--module-path=<PATH>) [--changelog=FILE] [--stampver=FILE] [--debug]
      SetPEVersion.py -h | --help
      SetPEVersion.py -v | --version

    Options:
      -c FILE --changelog=FILE    Specify the full path of "Changelog.txt"
      -s FILE --stampver=FILE     Specify the full path of "StampVer.exe"
      -m PATH --module-path=PATH  Specify a single module file(DLL or EXE) or a directory that contains module files
      -d --debug                  Show more messages for debug purpose
      -h --help                   Show this help message
      -v --version                Show version message
    """

    import docopt
    import pprint


    args = docopt.docopt(main.__doc__, version='SetPEVersion v0.1.0')
    changelog = _get_full_path(args['--changelog'], 'Changelog.txt')
    stampver = _get_full_path(args['--stampver'], 'StampVer.exe')

    if not os.path.isfile(changelog):
        perror('Changelog file not found at "{0}".'.format(changelog))

    if not os.path.isfile(stampver):
        perror('StampVer.exe not found at "{0}".'.format(changelog))

    modules = []
    if args['--module-path']:
        if os.path.isfile(args['--module-path']):
            modules.append(args['--module-path'])
        elif os.path.isdir(args['--module-path']):
            modules.extend(iterate_module_files_v3(args['--module-path']))
        else:
            perror('Invalid module path "{0}": Neither an existing file nor an existing directory.'.format(args['--module-path']))
    else:
        perror('"--module-path" option is required.')

    # Get the topmost line which contains a valid version number from Changelog.txt
    topmost_version_line = get_topmost_version_line(changelog)
    version_number = canonicalize_version_number(get_version_number(topmost_version_line))

    if args['--debug']:
        print('-' * 79)
        print(args)
        print(changelog)
        print(stampver)
        print(version_number)
        pprint.pprint(modules)
        print('-' * 79)

    for module in modules:
        # Code below does work for `StampVer.exe`.
        #cmd_args = (stampver, '-k', '-f"{0}"'.format(version_number), '-p"{0}"'.format(version_number), module)
        #subprocess.run(cmd_args)
        #
        # so I have to quote those arguments all by myself
        cmd_args = ' '.join((quote_path(stampver), '-k', '-f"{0}"'.format(version_number), '-p"{0}"'.format(version_number), quote_path(module)))
        run_subprocess(cmd_args)


if __name__ == '__main__':
    main()


# References:
# Ongoing-Study/cpp/msvc_cmdline_args/msvc_cmdline_args.cpp
# [Python glob multiple filetypes](http://stackoverflow.com/questions/4568580/python-glob-multiple-filetypes)
# https://github.com/telegramdesktop/tdesktop/blob/dev/Telegram/build/set_version.py
