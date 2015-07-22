#! /usr/bin/env python3
# coding: utf-8

# 2015-07-22T16:30+08:00

import functools
import os


# Several ways to walk/list a directory:
# (0) os.listdir
#     It can not walk a directory tree recursively. However, we can implement one
#     by ourselves(that's how os.walk works). The `stat` module's documentation
#     also give us a working example, called `walktree`.
# (1) os.walk
#     Internally, it calls `os.listdir` to do the listing work for each sub-directory.
# (2) pathlib.Path.iterdir
#     New in Python v3.4. I haven't take a look at it yet.
# (3) scandir
#     New in Python v3.5. I haven't take a look at it yet. The README.md on GitHub says
#     that it is faster than `os.walk`.


# This function is inspired by `os.walk`, but they have different behaviours.
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


def list_files(top, recursively=True, topdown=True, onerror=None, followlinks=False):
    """List all files under specified directory."""
    if recursively:
        for root, subdirs, files in os.walk(top, topdown, onerror, followlinks):
            fullpath = functools.partial(os.path.join, root)
            yield from map(fullpath, files)
    else:
        yield from filter(os.path.isfile, walk(top, recursively))


def list_subdirs(top, recursively=True, topdown=True, onerror=None, followlinks=False):
    """List all sub-directories under specified directory."""
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
        
        how_many_files = length(list_files(rootdir, recursively))
        how_many_subdirs = length(list_subdirs(rootdir, recursively))
        total = length(walk(rootdir, recursively))
        
        assert total == how_many_files + how_many_subdirs
        
        print('How many files?', how_many_files)
        print('How many directories?', how_many_subdirs)
        print('Totally:', total)

