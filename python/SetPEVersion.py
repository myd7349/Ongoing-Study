# -*- coding: utf-8 -*-

# 2016-10-20T16:00+08:00


import os
import re
import sys


# Match version numbers of these formats:
# 1.2.3
# 1.2.3.4
version_number_re = r'([0-9]+(?:.[0-9]+){2,3})'

# Match version numbers of this format:
incomplete_version_number_re = r'^[0-9]+(?:.[0-9]+){2}$'

# Match a line, in Changelog.txt, which contains a valid version number
version_line_re = r'^### v{0}.*$'.format(version_number_re)


def get_topmost_version_line(changelog_file, encoding='utf-8'):
    with open(changelog_file, 'r', encoding=encoding) as fp:
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


def _get_full_path(candidate_path, file_name):
    if candidate_path is None:
        candidate_path = ''

    if os.path.isfile(candidate_path):
        return candidate_path
    elif os.path.isdir(candidate_path):
        return os.path.join(candidate_path, file_name)
    else:
        return os.path.join(os.path.dirname(sys.argv[0]), file_name)


def main():
    """
    Usage:
      SetPEVersion.py (--module=<FILE> | --module-dir=<FILE>) [--changelog=FILE] [--stampver=FILE] [--debug]
      SetPEVersion.py -h | --help
      SetPEVersion.py -v | --version

    Options:
      -c FILE --changelog=FILE  Specify the full path of "Changelog.txt"
      -s FILE --stampver=FILE   Specify the full path of "StampVer.exe"
      -m FILE --module=FILE     Specify the module file(DLL or EXE) to be processed
      --module-dir=DIR          Specify the module directory
      -d --debug                Show more messages for debug propose
      -h --help                 Show this help message
      -v --version              Show version message
    """

    import docopt
    import fnmatch
    import pprint
    import subprocess


    args = docopt.docopt(main.__doc__, version='SetPEVersion v0.1.0')
    changelog = _get_full_path(args['--changelog'], 'Changelog.txt')
    stampver = _get_full_path(args['--stampver'], 'StampVer.exe')

    if not os.path.isfile(changelog):
        perror('Changelog file not found at "{0}".'.format(changelog))

    if not os.path.isfile(stampver):
        perror('StampVer.exe not found at "{0}".'.format(changelog))

    modules = []
    if args['--module']:
        if not os.path.isfile(args['--module']):
            perror('Specified module file "{0}" doesn\'t exist.\n'.format(module))
        else:
            modules.append(args['--module'])
    elif args['--module-dir']:
        if not os.path.isdir(args['--module-dir']):
            perror('"{0}" is not a valid directory.'.format(args['--module-dir']))
        else:
            for file in filter(os.path.isfile,
                               map(lambda item_name: os.path.join(args['--module-dir'], item_name),
                                   map(lambda item: item.name,
                                       os.scandir(args['--module-dir'])))):
                print(file)
                if fnmatch.fnmatch(file, '*.dll') or fnmatch.fnmatch(file, '*.exe'):
                    modules.append(file)
    else:
        perror('"--module"/"--module-dir" option is required.')

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
        cmd_args = [stampver, '-k', '-f"{0}"'.format(version_number), '-p"{0}"'.format(version_number), module]
        subprocess.run(cmd_args)


if __name__ == '__main__':
    main()
