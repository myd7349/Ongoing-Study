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
