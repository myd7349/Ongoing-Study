#!/usr/bin/env python3
# coding: utf-8

import os
import subprocess


if os.name == 'nt':
    _print_argv_len = 'print_argv_len.exe'
else:
    _print_argv_len = 'print_argv_len.o'

_argv0_len = len(_print_argv_len)


def call_print_argv_len(argv_len):
    assert(argv_len > _argv0_len)

    argv1_len = argv_len - _argv0_len
    argv = (_print_argv_len, 'A' * argv1_len)

    try:
        return subprocess.run(argv).returncode
    except:
        return -1


def main():
    begin, end = 2000, 65536

    while True:
        argv_len = (begin + end) // 2
        print(f'Try {argv_len} == ({begin} + {end}) / 2...')

        rc = call_print_argv_len(argv_len)

        print(f'Return code: {rc}')

        if begin == end:
            break

        if argv_len == rc:
            begin = argv_len
        elif rc == -1:
            end = argv_len
        else:
            end = argv_len
            break


if __name__ == '__main__':
    main()


# References:
# [Maximum Length of Command Line String](https://stackoverflow.com/questions/3205027/maximum-length-of-command-line-string)
# > On computers running Microsoft Windows XP or later, the maximum length of the string that you can use at the command prompt is 8191 characters.
# [Is there any limit on line length when pasting to a terminal in Linux?](https://unix.stackexchange.com/questions/643777/is-there-any-limit-on-line-length-when-pasting-to-a-terminal-in-linux)
# > 4095 is the limit of the tty line discipline internal editor length on Linux.
# [How to get exit code when using Python subprocess communicate method?](https://stackoverflow.com/questions/5631624/how-to-get-exit-code-when-using-python-subprocess-communicate-method)
# https://docs.python.org/3/library/subprocess.html
