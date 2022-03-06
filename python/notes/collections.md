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

[Equality overloading for namedtuple](https://stackoverflow.com/questions/34570814/equality-overloading-for-namedtuple)

[How to cast namedtuple into tuple](https://stackoverflow.com/questions/55633358/how-to-cast-namedtuple-into-tuple)

[Python 有序字典的实现](https://frostming.com/2016/07-07/python-you-xu-zi-dian-de-shi-xian/)

https://github.com/python/cpython/blob/9be0b2e3122b8cb3078367e667bb6ab58cd81610/Lib/collections.py

```python
class OrderedDict(dict):
    def __init__(self, *args, **kwds):
        if len(args) > 1:
            raise TypeError('expected at most 1 arguments, got %d' % len(args))
        try:
            self.__root
        except AttributeError:
            self.__root = root = []                     # sentinel node
            root[:] = [root, root, None]
            self.__map = {}
        self.__update(*args, **kwds)

    def __setitem__(self, key, value, dict_setitem=dict.__setitem__):
        'od.__setitem__(i, y) <==> od[i]=y'
        # Setting a new item creates a new link which goes at the end of the linked
        # list, and the inherited dictionary is updated with the new key/value pair.
        if key not in self:
            root = self.__root
            last = root[0]
            last[1] = root[0] = self.__map[key] = [last, root, key]
        dict_setitem(self, key, value)

    def __delitem__(self, key, dict_delitem=dict.__delitem__):
        'od.__delitem__(y) <==> del od[y]'
        # Deleting an existing item uses self.__map to find the link which is
        # then removed by updating the links in the predecessor and successor nodes.
        dict_delitem(self, key)
        link_prev, link_next, key = self.__map.pop(key)
        link_prev[1] = link_next
        link_next[0] = link_prev
```

https://github.com/pydata/xarray/blob/main/xarray/backends/lru_cache.py

