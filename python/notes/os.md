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
