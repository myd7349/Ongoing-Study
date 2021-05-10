2017-11-13T20:13+08:00

shutil.py:
```python
if hasattr(os, 'statvfs'):

    __all__.append('disk_usage')
    _ntuple_diskusage = collections.namedtuple('usage', 'total used free')
    _ntuple_diskusage.total.__doc__ = 'Total space in bytes'
    _ntuple_diskusage.used.__doc__ = 'Used space in bytes'
    _ntuple_diskusage.free.__doc__ = 'Free space in bytes'
```

[Does Python have an ordered set?](https://stackoverflow.com/questions/1653970/does-python-have-an-ordered-set)

