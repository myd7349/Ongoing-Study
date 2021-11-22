#!/usr/bin/env python3
# coding: utf-8

import os.path
from pathlib import Path
import sys


def main():
    start_path = Path(sys.argv[1]) if len(sys.argv) > 1 else Path.cwd()

    files = Path(start_path).rglob('*.amr')
    files_sorted = sorted(files, key=os.path.getctime)

    count = 1
    for file in files_sorted:
        print('{0:03d}: {1} {2}'.format(count, os.path.getctime(file), file))
        file.rename('{0:03d}.{1}'.format(count, file.suffix))
        count += 1


if __name__ == '__main__':
    main()


# References:
# https://github.com/whtsky/kindle-sdr-cleaner
# [Changing file extension in Python](https://stackoverflow.com/questions/2900035/changing-file-extension-in-python)
# [Recursively iterate through all subdirectories using pathlib](https://stackoverflow.com/questions/50714469/recursively-iterate-through-all-subdirectories-using-pathlib)
# [How do you get a directory listing sorted by creation date in python?](https://stackoverflow.com/questions/168409/how-do-you-get-a-directory-listing-sorted-by-creation-date-in-python)
