#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-03-24T08:33+08:00

import functools
import io
import os

def file_size(f):
    '''Get the size of given file.

    f: File name or an opened file object
    '''
    
    if not all(map(functools.partial(hasattr, f),
                   ['read', 'fileno', 'seek', 'tell'])):
        return os.stat(f).st_size

    try:
        return os.fstat(f.fileno()).st_size
    except io.UnsupportedOperation:
        prev_pos = f.tell()
        size = f.seek(0, os.SEEK_END)
        f.seek(prev_pos, os.SEEK_SET)
        return size

def replace_ext(file, new_ext):
    '''Produce a new file name based on input file name with its extension
    replaced with a new extension.

    file: Source file name
    new_ext: The new extension to be used
    '''

    root, ext = os.path.splitext(file)
    return root + new_ext if ext else file + new_ext

if __name__ == '__main__':
    import unittest
    
    class TestFileSize(unittest.TestCase):
        def test_regular_file(self):
            test_file = 'fpsize_test.dat'
            data = b'Hello, world'
            try:
                with open(test_file, 'wb') as fp:
                    fp.write(data)
                    fp.flush()

                    self.assertEqual(file_size(fp), len(data))
            finally:
                self.assertEqual(file_size(test_file), len(data))
                os.remove(test_file)

        def test_bytes_buffer(self):
            buffer = b'Hello, world!'
            pseudo_file = io.BytesIO(buffer)

            self.assertRaises(io.UnsupportedOperation, pseudo_file.fileno)
            self.assertEqual(pseudo_file.read(5), b'Hello')
            self.assertEqual(pseudo_file.tell(), 5)
            self.assertEqual(file_size(pseudo_file), len(buffer))
            self.assertEqual(pseudo_file.tell(), 5)
            self.assertEqual(pseudo_file.read(), b', world!')

    class TestReplaceExt(unittest.TestCase):
        def test(self):
            file1 = 'a.out'
            self.assertEqual(replace_ext(file1, '.exe'), 'a.exe')

            file2 = '.cshrc'
            self.assertEqual(replace_ext(file2, '.conf'), file2 + '.conf')

            self.assertEqual(replace_ext('foo', '.dcm'), 'foo.dcm')
            
    unittest.main()
    
# References:
# [Size of an open file object](http://stackoverflow.com/questions/283707/size-of-an-open-file-object)
