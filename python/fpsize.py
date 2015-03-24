#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-03-24T08:33+08:00

import functools
import io
import os

def fp_size(fp):
    '''Get the size of given file object.'''
    if not all(map(functools.partial(hasattr, fp), ['read', 'fileno', 'seek', 'tell'])):
        raise ValueError('Invalid file object')

    try:
        return os.fstat(fp.fileno()).st_size
    except io.UnsupportedOperation:
        prev_pos = fp.tell()
        size = fp.seek(0, os.SEEK_END)
        fp.seek(prev_pos, os.SEEK_SET)
        return size

if __name__ == '__main__':
    import unittest
    
    class TestFPSize(unittest.TestCase):
        def test_regular_file(self):
            test_file = 'fpsize_test.dat'
            try:
                with open(test_file, 'wb') as fp:
                    data = b'Hello, world'
                    fp.write(data)
                    fp.flush()

                    self.assertEqual(fp_size(fp), len(data))
            finally:
                os.remove(test_file)

        def test_bytes_buffer(self):
            buffer = b'Hello, world!'
            pseudo_file = io.BytesIO(buffer)

            self.assertRaises(io.UnsupportedOperation, pseudo_file.fileno)
            self.assertEqual(pseudo_file.read(5), b'Hello')
            self.assertEqual(pseudo_file.tell(), 5)
            self.assertEqual(fp_size(pseudo_file), len(buffer))
            self.assertEqual(pseudo_file.tell(), 5)


    unittest.main()
    
# References:
# [Size of an open file object](http://stackoverflow.com/questions/283707/size-of-an-open-file-object)
