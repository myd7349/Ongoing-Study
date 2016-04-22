#! /usr/bin/env python3
# coding: utf-8

# 2015-07-22T16:30+08:00

import functools
import os


# Several ways to walk/list a directory:
# (0) os.listdir
#     It can not walk a directory tree recursively. However, we can implement one
#     by ourselves(that's how `os.walk` before Python 3.5 works). The `stat` module's
#     documentation also give us a working example, called `walktree`.
# (1) os.walk
#     Internally, it calls `os.listdir` to do the listing work for each sub-directory.
#     (That is not the case since Python 3.5.)
# (2) pathlib.Path.iterdir
#     New in Python v3.4. I haven't take a look at it yet.
# (3) os.scandir
#     New in Python v3.5. The README at:
#         https://github.com/benhoyt/scandir/blob/master/README.rst
#     says that it is faster than the previous version of `os.walk`.
#     In Python 3.5, `os.walk` calls `os.scandir` instead of `os.listdir`.
# (4) This one is cool.
#     https://github.com/eliben/pss/blob/master/psslib/filefinder.py


# This function is inspired by `os.walk`, but they have different behaviours.
# TODO: Replace the call to `os.listdir` with `os.scandir`.
def _walk_recursively_impl(top, topdown=True, onerror=None, followlinks=False):
    try:
        items = os.listdir(top)
    except OSError as err:
        if onerror is not None:
            onerror(err)
        return

    fullpath = functools.partial(os.path.join, top)

    for item in items:
        item_fullpath = fullpath(item)
        if topdown:
            yield item_fullpath
        if os.path.isdir(item_fullpath) and (followlinks or not os.path.islink(item_fullpath)):
            yield from _walk_recursively_impl(item_fullpath, topdown, onerror, followlinks)
        if not topdown:
            yield item_fullpath


def walk(top, recursively=True, topdown=True, onerror=None, followlinks=False):
    """Walk a specified directory."""
    if recursively:
        yield from _walk_recursively_impl(top, topdown, onerror, followlinks)
    else:
        fullpath = functools.partial(os.path.join, top)
        yield from map(fullpath, os.listdir(top))


def ifile(top, recursively=True, topdown=True, onerror=None, followlinks=False):
    """Iterate all files under specified directory."""
    if recursively:
        for root, subdirs, files in os.walk(top, topdown, onerror, followlinks):
            fullpath = functools.partial(os.path.join, root)
            yield from map(fullpath, files)
    else:
        yield from filter(os.path.isfile, walk(top, recursively))


def isubdir(top, recursively=True, topdown=True, onerror=None, followlinks=False):
    """Iterate all sub-directories under specified directory."""
    if recursively:
        for root, subdirs, files in os.walk(top, topdown, onerror, followlinks):
            fullpath = functools.partial(os.path.join, root)
            yield from map(fullpath, subdirs)
    else:
        yield from filter(os.path.isdir, walk(top, recursively))


if __name__ == '__main__':
    rootdir = os.path.dirname(os.path.dirname(__file__))
    print(rootdir)

    length = lambda iterable: len(list(iterable))

    for recursively in (True, False):
        print('-' * 79)

        how_many_files = length(ifile(rootdir, recursively))
        how_many_subdirs = length(isubdir(rootdir, recursively))
        total = length(walk(rootdir, recursively))

        assert total == how_many_files + how_many_subdirs

        print('How many files?', how_many_files)
        print('How many directories?', how_many_subdirs)
        print('Totally:', total)
