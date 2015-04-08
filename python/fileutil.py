#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-03-24T08:33+08:00

import functools
import io
import os

def is_file_object(f):
    if not all(map(functools.partial(hasattr, f),
                   ['read', 'fileno', 'seek', 'tell'])):
        return False
    return True
    
def file_size(f):
    '''Get the size of given file.

    f: File name or an opened file object
    '''

    if isinstance(f, str):
        return os.stat(f).st_size

    if not is_file_object(f):
        raise ValueError('Invalid file object')

    try:
        return os.fstat(f.fileno()).st_size
    except io.UnsupportedOperation:
        prev_pos = f.tell()
        size = f.seek(0, os.SEEK_END)
        f.seek(prev_pos, os.SEEK_SET)
        return size

def file_name(f):
    '''Retrieve the name of given file.

    f: File name or an opened file object
    '''
    if isinstance(f, str):
        return f

    if is_file_object(f):
        return getattr(f, 'name', '')
    else:
        return ''

def replace_ext(file, new_ext, prefix = '', suffix = ''):
    '''Produce a new file name based on input file name with its extension
    replaced with a new extension.

    file: Source file name
    new_ext: The new extension to be used
    '''

    root, ext = os.path.splitext(file)
    return prefix + root + suffix + new_ext if ext else prefix + file + suffix + new_ext

class FileGuard:
    '''Sometimes when we wrote a function that accepts an file object, we also
    want it be able to deal with file name. So some code like this:
        def foo(f):
            'Some function that handling an input file.'
            if isinstance(f, str):
                # A file name is passed in, let's open it.
                fp = open(f, 'r')
            else:
                # Suppose that an opened file object is passed in.
                assert hasattr(f, 'read')
                fp = f
    has been written.
    
    When it comes to a file name, it will be nice to wrap it with a `with` statement,
    like this:
        with open(f, 'r') as fp:
            pass

    With this class, we can rewrite `foo` like this:
        def foo(f):
            'Some function that handling an input file.'
            with FileGuard(f, 'r') as fp:
                pass
    and if you passed a file name to `foo`, the file will be automatically closed when
    FileGuard.__exit__ is executed. If you passed an opened file object, however,
    FileGuard.__exit__ will do nothing. Sounds nice, hah?
    '''
    def __init__(self, file, *args, **kwargs):
        if isinstance(file, str):
            self._file = open(file, *args, **kwargs)
            self._user_owned_the_file = False
        else:
            self._file = file
            self._user_owned_the_file = True
    
    def __enter__(self):
        return self._file

    def __exit__(self, exc_type, exc_value, traceback):
        if not self._user_owned_the_file:
            self._file.close()

def open_file(file, *args, **kwargs):
    return FileGuard(file, *args, **kwargs)

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

    class TestFileName(unittest.TestCase):
        def setUp(self):
            self._file = 'a.out'
            
        def test_file_name(self):
            self.assertEqual(file_name(self._file), self._file)

        def test_file_object(self):
            with open(self._file, 'w') as fp:
                self.assertEqual(file_name(fp), self._file)
            os.remove(self._file)

        def test_buffer_object(self):
            buffer = b'Howdy, world!'
            pseudo_file = io.BytesIO(buffer)

            self.assertEqual(file_name(pseudo_file), '')

    class TestReplaceExt(unittest.TestCase):
        def setUp(self):
            self._file = 'a.out'
            
        def test(self):
            self.assertEqual(replace_ext(self._file, '.exe'), 'a.exe')

            file2 = '.cshrc'
            self.assertEqual(replace_ext(file2, '.conf'), file2 + '.conf')

            self.assertEqual(replace_ext('foo', '.dcm'), 'foo.dcm')

        def test_prefix_suffix(self):
            self.assertEqual(replace_ext(self._file, '.exe', 'WOW-', '-2'), 'WOW-a-2.exe')
            self.assertEqual(replace_ext('foo', '.dcm', suffix = '-0'), 'foo-0.dcm')
            self.assertEqual(replace_ext('foo', '.dcm', suffix = '-1'), 'foo-1.dcm')
            self.assertEqual(replace_ext('foo', '.dcm', suffix = '-2'), 'foo-2.dcm')
            

    class TestOpenFile(unittest.TestCase):
        def test_pass_a_file_name(self):
            file = 'a.out'
            test_data = b'Hello, world!'
            fp = None
            
            if not os.path.exists(file):
                with open_file(file, 'wb') as fp:
                    fp.write(test_data)
                self.assertTrue(fp.closed)

                os.remove(file)

        def test_pass_a_file_object(self):
            file = 'a.out'
            test_data = b'myd7349'
            
            if not os.path.exists(file):
                f = open(file, 'w+b')
                with open_file(f, 'w+b') as fp:
                    fp.write(test_data)
                self.assertFalse(f.closed)
                f.seek(0, 0)
                self.assertEqual(f.read(), test_data)
                f.close()
                os.remove(file)
            
    unittest.main()
    
# References:
# [Does filehandle get closed automatically in Python after it goes out of scope?](http://stackoverflow.com/questions/2404430/does-filehandle-get-closed-automatically-in-python-after-it-goes-out-of-scope)
# [Does a File Object Automatically Close when its Reference Count Hits Zero?](http://stackoverflow.com/questions/1834556/does-a-file-object-automatically-close-when-its-reference-count-hits-zero)
# [Explaining Python's '__enter__' and '__exit__'](http://stackoverflow.com/questions/1984325/explaining-pythons-enter-and-exit)
# [Is close() necessary when using iterator on a Python file object](http://stackoverflow.com/questions/1832528/is-close-necessary-when-using-iterator-on-a-python-file-object)
# [Python file with closing automatically](http://www.peterbe.com/plog/python-file-with-closing-automatically)
# [Size of an open file object](http://stackoverflow.com/questions/283707/size-of-an-open-file-object)
# [Understanding Python's "with" statement](http://effbot.org/zone/python-with-statement.htm)
