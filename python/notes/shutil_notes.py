#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2017-01-11T17:28:25+08:00

import os.path
import shutil

import humanize  # pip install humanize



def list_drives():
    return [chr(d) + ':'
            for d in range(ord('A'), ord('Z') + 1)
            if os.path.exists(chr(d) + ':')]


def get_usage(drive):
    if not os.path.exists(drive):
        return ''

    usage = shutil.disk_usage(drive)
    return usage._replace(**{k: humanize.naturalsize(v) for k, v in usage._asdict().items()})


def list_disk_usages():
    for d in list_drives():
        print(d, get_usage(d))


def main():
    list_disk_usages()


if __name__ == '__main__':
    main()
