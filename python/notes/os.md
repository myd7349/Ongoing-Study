##### os.devnull

2016-11-28T15:00+08:00

[Google/benchmark](https://github.com/google/benchmark)/mingw.py:

```python
def unpack(archive, location, log = EmptyLogger()):
    '''
    Unpacks a mingw-builds archive
    '''
    sevenzip = find_7zip(log)
    log.info('unpacking %s', os.path.basename(archive))
    cmd = [sevenzip, 'x', archive, '-o' + location, '-y']
    log.debug(' - %r', cmd)
    with open(os.devnull, 'w') as devnull:
        subprocess.check_call(cmd, stdout = devnull)
```

This code snippet shows when to use `os.devnull`.

##### os.replace

https://github.com/psf/requests/blob/main/requests/utils.py

```python
@contextlib.contextmanager
def atomic_open(filename):
    """Write a file to the disk in an atomic fashion"""
    replacer = os.rename if sys.version_info[0] == 2 else os.replace
    tmp_descriptor, tmp_name = tempfile.mkstemp(dir=os.path.dirname(filename))
    try:
        with os.fdopen(tmp_descriptor, 'wb') as tmp_handler:
            yield tmp_handler
        replacer(tmp_name, filename)
    except BaseException:
        os.remove(tmp_name)
        raise
```

https://docs.python.org/3/library/os.html

> If you want cross-platform overwriting of the destination, use [`replace()`](https://docs.python.org/3/library/os.html#os.replace).

