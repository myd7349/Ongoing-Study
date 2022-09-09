[How can I remove a key from a Python dictionary?](https://stackoverflow.com/questions/11277432/how-can-i-remove-a-key-from-a-python-dictionary)

[pefile/pefile.py at e3514208aa120200ca689c85a23e05f19233a503 · erocarrera/pefile · GitHub](https://github.com/erocarrera/pefile/blob/e3514208aa120200ca689c85a23e05f19233a503/pefile.py#L136-L137)

> ```python
> def two_way_dict(pairs):
>     return dict([(e[1], e[0]) for e in pairs] + pairs)
> ```


[twodict](https://github.com/MrS0m30n3/twodict)

 [How can I make a dictionary from separate lists of keys and values?](https://stackoverflow.com/questions/209840/how-can-i-make-a-dictionary-from-separate-lists-of-keys-and-values)

```python
keys = ['a', 'b', 'c']
values = [1, 2, 3]
dictionary = dict(zip(keys, values))
print(dictionary) # {'a': 1, 'b': 2, 'c': 3}
```

[Case insensitive dictionary](https://stackoverflow.com/questions/2082152/case-insensitive-dictionary)

https://github.com/kennethreitz/requests/blob/v1.2.3/requests/structures.py#L37

[Case insensitive dictionary search?](https://stackoverflow.com/questions/3296499/case-insensitive-dictionary-search)

```python
dict(zip(map(string.lower,a.keys()),a.values()))
```

https://peps.python.org/pep-0455/

[Python dictionary: are keys() and values() always the same order?](https://stackoverflow.com/questions/835092/python-dictionary-are-keys-and-values-always-the-same-order)

https://github.com/aio-libs/multidict

[How to create key or append an element to key?](https://stackoverflow.com/questions/12905999/how-to-create-key-or-append-an-element-to-key)

https://github.com/urllib3/urllib3/pull/2336/files

```
# Starting in Python 3.7 the 'dict' class is guaranteed to be
# ordered by insertion. This behavior was an implementation
# detail in Python 3.6. OrderedDict is implemented in C in
# later Python versions but still requires a lot more memory
# due to being implemented as a linked list.
```
