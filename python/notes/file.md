[How we can truncate a file at a given size using Python?](https://www.tutorialspoint.com/How-we-can-truncate-a-file-at-a-given-size-using-Python)

> ```python
> f = open(r'data.dat', 'r+')
> f.truncate(1000)
> print(f.read())
> f.close()
> ```

[Iterate blocks of a file](https://github.com/avalentino/hashsum/blob/1bc36e78439ee066626d7875fc4e8ae20f0aa2f8/hashsum.py#L59-L69)

> ```python
> def blockiter(fd, blocksize=io.DEFAULT_BUFFER_SIZE):
>     """Iterate on file-like objects reading blocks of the specified size.
>     The `fd` parameter must be a binary or text file-like object opened
>     for reading.
>     The `blocksize` parameter defaults to `io.DEFAULT_BUFFER_SIZE`.
>     """
>     guard = '' if isinstance(fd, io.TextIOBase) else b''
> 
>     return iter(functools.partial(fd.read, blocksize), guard)
> ```

[ReplaceStringsInFile](https://github.com/abseil/abseil-cpp/blob/20211102.0/create_lts.py)

[Does for line in File read entire file](https://stackoverflow.com/questions/29133556/does-for-line-in-file-read-entire-file)

```python
filepath = 'pocketfft.cpp'

with open(filepath, "r") as f:
    return "cppimport" in f.readline()
```

Error message:

```
Python 3.9.12 (main, Apr  4 2022, 05:22:27) [MSC v.1916 64 bit (AMD64)] :: Anaconda, Inc. on win32
Type "help", "copyright", "credits" or "license" for more information.
>>> import cppimport.import_hook
>>> import pocketfft
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
  File "<frozen importlib._bootstrap>", line 1007, in _find_and_load
  File "<frozen importlib._bootstrap>", line 982, in _find_and_load_unlocked
  File "<frozen importlib._bootstrap>", line 925, in _find_spec
  File "C:\Users\myd7349\AppData\Roaming\Python\Python39\site-packages\cppimport\import_hook.py", line 21, in find_spec
    cppimport.imp(fullname, opt_in=True)
  File "C:\Users\myd7349\AppData\Roaming\Python\Python39\site-packages\cppimport\__init__.py", line 49, in imp
    filepath = find_module_cpppath(fullname, opt_in)
  File "C:\Users\myd7349\AppData\Roaming\Python\Python39\site-packages\cppimport\find.py", line 12, in find_module_cpppath
    filepath = _find_module_cpppath(modulename, opt_in)
  File "C:\Users\myd7349\AppData\Roaming\Python\Python39\site-packages\cppimport\find.py", line 32, in _find_module_cpppath
    outfilename = _find_file_in_folders(modulefilename, abs_matching_dirs, opt_in)
  File "C:\Users\myd7349\AppData\Roaming\Python\Python39\site-packages\cppimport\find.py", line 72, in _find_file_in_folders
    if opt_in and not _check_first_line_contains_cppimport(filepath):
  File "C:\Users\myd7349\AppData\Roaming\Python\Python39\site-packages\cppimport\find.py", line 84, in _check_first_line_contains_cppimport
    return "cppimport" in f.readline()
UnicodeDecodeError: 'gbk' codec can't decode byte 0x80 in position 2868: illegal multibyte sequence
>>>
```

> 'gbk' codec can't decode byte 0x80 in position **2868**: illegal multibyte sequence
