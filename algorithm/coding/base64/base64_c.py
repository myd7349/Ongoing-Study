#! /usr/bin/env python3
# encoding: utf-8

import ctypes
import ctypes.util
import os
import os.path
import shlex
import subprocess
import sys


def _quote_path(path):
    if os.name == 'nt':
        return '"{0}"'.format(path)
    else:
        return shlex.quote(path)


def _search_base64_dylib(build_path):
    known_names = frozenset(('base64.dll', 'libbase64.so', 'libbase64.dylib'))
    for root, dirs, files in os.walk(build_path):
        for f in files:
            if f in known_names:
                return os.path.join(root, f)


def _load_base64_module():
    current_path = os.path.dirname(__file__)
    build_path = os.path.join(current_path, 'build')
    install_path = os.path.join(build_path, "install")

    os.makedirs(build_path, exist_ok=True)
    
    subprocess.run([
        'cmake',
        '..',
        '-DBUILD_SHARED_LIBS=ON',
        '-DCMAKE_INSTALL_PREFIX={0}'.format(_quote_path(install_path))
        ],
        cwd=build_path,
        )
    subprocess.run([
        'cmake',
        '--build',
        '.',
        '--config',
        'Release'
        ],
        cwd=build_path,
        )

    dylib_path = _search_base64_dylib(build_path)
    if not dylib_path:
        raise RuntimeError("Could not find base64 dynamic library!")

    print('base64 library path: {0}'.format(dylib_path))
    return ctypes.CDLL(dylib_path)


_base64_module = _load_base64_module()

_base64_encoded_length = _base64_module.base64_encoded_length
_base64_encoded_length.restype = ctypes.c_size_t
_base64_encoded_length.argtypes = (ctypes.c_size_t, ctypes.c_int)

_base64_decoded_length = _base64_module.base64_decoded_length_slow
_base64_decoded_length.restype = ctypes.c_size_t
_base64_decoded_length.argtypes = (ctypes.c_void_p, ctypes.c_size_t, ctypes.c_int)

_base64_encode_decode_prototype = ctypes.CFUNCTYPE(
    ctypes.c_void_p,
    ctypes.c_void_p, ctypes.c_size_t,
    ctypes.c_void_p, ctypes.POINTER(ctypes.c_size_t),
    ctypes.c_int)
_base64_encode = _base64_encode_decode_prototype(('base64_encode', _base64_module))
_base64_decode = _base64_encode_decode_prototype(('base64_decode', _base64_module))

B64F_NORMAL     = 0x01
B64F_URLSAFE    = 0x02
B64F_NO_PADDING = 0x10


def base64_encode(data, flags=B64F_NORMAL):
    if not isinstance(data, (bytes, bytearray, memoryview)):
        raise TypeError("Expected bytes-like object, not {0}".format(data.__class__.__name__))

    in_len = len(data)

    expected_len_raw = _base64_encoded_length(in_len, flags)
    expected_len = ctypes.c_size_t(expected_len_raw)
    out_buffer = ctypes.cast(
        ctypes.create_string_buffer(expected_len_raw),
        ctypes.c_void_p)

    _base64_encode(
        bytes(data), in_len,
        out_buffer, ctypes.byref(expected_len),
        flags)

    #return ctypes.cast(out_buffer, ctypes.c_char_p).value[:expected_len_raw]
    return ctypes.string_at(out_buffer, expected_len_raw)


def base64_decode(bstr, flags=B64F_NORMAL):
    if not isinstance(bstr, (bytes, bytearray, memoryview, str)):
        raise TypeError("Expected string-like object, not {0}".format(data.__class__.__name__))

    if bstr is str:
        bstr = bstr.encode('ascii')

    in_len = len(bstr)

    expected_len_raw = _base64_decoded_length(bytes(bstr), in_len, flags)
    expected_len = ctypes.c_size_t(expected_len_raw)
    out_buffer = ctypes.cast(
        ctypes.create_string_buffer(expected_len_raw),
        ctypes.c_void_p)

    _base64_decode(
        bytes(bstr), in_len,
        out_buffer, ctypes.byref(expected_len),
        flags)

    return ctypes.string_at(out_buffer, expected_len.value)


def do_test(data, flags=B64F_NORMAL):
    print('-' * 79)
    
    print('RawData:', data)
    
    encoded_data = base64_encode(data, flags)
    print('Encoded:', encoded_data)

    decoded_data = base64_decode(encoded_data, flags)
    print('Decoded:', decoded_data)


if __name__ == '__main__':
    do_test(bytearray(b'\x00'))
    do_test(bytearray(b'\x00'), B64F_NORMAL | B64F_NO_PADDING)
    do_test(b'\x00\x00')
    do_test(b'\x00\x00', B64F_NORMAL | B64F_NO_PADDING)
    do_test(b'\x00\x00\x00')
    do_test(b'Hello, world')
    do_test(b'Hello, world!')
    do_test(b'Hello, world!', B64F_NORMAL | B64F_NO_PADDING)
    do_test(b'\x04B<\x96\xaa\x0e\xdae\x94U{\xd5]\xaat\xb6\xd5_')
    do_test(b'\x99\x00`\xd2R\xae')
    do_test(b'\xce_{\xad')


# References:
# https://stackoverflow.com/questions/28941133/what-is-the-encoding-of-the-subprocess-module-output-in-python-2-7
# https://stackoverflow.com/questions/20950612/python-ctypes-integer-pointer
# https://stackoverflow.com/questions/26277322/passing-arrays-with-ctypes
# https://stackoverflow.com/questions/33813272/python-ctypes-pass-c-void-p-as-an-out-parameter-to-c-function
# https://stackoverflow.com/questions/46171507/passing-a-byte-array-to-a-c-function-that-accepts-a-void-pointer
# https://stackoverflow.com/questions/16676739/python-ctypes-how-to-pass-void-as-argument
# https://stackoverflow.com/questions/1546355/using-enums-in-ctypes-structure
# http://code.activestate.com/recipes/576415/
# https://github.com/ActiveState/code/blob/master/recipes/Python/576415_ctype_Enumeration_class/recipe-576415.py
# https://stackoverflow.com/questions/1615813/how-to-use-c-classes-with-ctypes
# https://stackoverflow.com/questions/6221001/calling-uname-from-libc-with-pythons-ctypes
# https://stackoverflow.com/questions/18679264/how-to-use-malloc-and-free-with-python-ctypes
# https://stackoverflow.com/questions/1363163/pointers-and-arrays-in-python-ctypes
# https://stackoverflow.com/questions/15377338/convert-ctype-byte-array-to-bytes
# https://stackoverflow.com/questions/24912065/how-to-access-data-from-pointer-in-struct-from-python-with-ctypes
# https://stackoverflow.com/questions/54357920/python-ctypes-create-bytearray-from-void
# https://stackoverflow.com/questions/1825715/how-to-pack-and-unpack-using-ctypes-structure-str
# https://github.com/labstreaminglayer/pylsl/blob/master/pylsl/pylsl.py
