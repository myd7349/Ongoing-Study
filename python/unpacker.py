#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-06-04T10:33+08:00

import io
import os.path
import struct
import sys

import fileutil


def unpack_data(buf, fmt, offset=0):
    """Retrieve data from given data buffer and unpack them according to specified format."""
    if not isinstance(buf, (bytes, bytearray)):
        raise ValueError('Invalid data buffer')

    return unpack_data_from_file(io.BytesIO(buf), fmt, offset)


def unpack_data_from_file(file, fmt, offset=0):
    """Retrieve data from given file and unpack them according to specified format.

    file: The path name of the file or an opened file object
    fmt: Format specification
    offset: Offset from the start of the file from where to start the unpacking operation
    """
    if isinstance(file, str):
        if not os.path.isfile(file):
            raise ValueError('"{}" is not a regular file'.format(file))
    else:
        if not hasattr(file, 'read'):
            raise ValueError('Invalid file object')
        if hasattr(file, 'mode') and file.mode != 'rb':
            raise ValueError('Invalid opening mode')

    if not isinstance(offset, int) or offset < 0:
        raise ValueError('Invalid offset value')

    with fileutil.open_file(file, 'rb') as fp:
        file_len = fileutil.file_size(fp)
        pack_size = struct.calcsize(fmt)

        if file_len <= offset:
            return

        fp.seek(offset, os.SEEK_SET)

        if (file_len - offset) % pack_size == 0:
            if sys.version_info >= (3, 3):
                #return struct.iter_unpack(fmt, fp.read())  # Fix issue #1
                yield from struct.iter_unpack(fmt, fp.read())
            else:
                for unpacked_data in struct.iter_unpack(fmt, fp.read()):
                    yield unpacked_data
        else:
            # The length of the file isn't the multiple of struct.calcsize(fmt), so
            # don't calling struct.iter_unpack directly.
            data = fp.read(pack_size)
            while data:
                if len(data) == pack_size:
                    yield struct.unpack(fmt, data)
                else:
                    break
                data = fp.read(pack_size)
