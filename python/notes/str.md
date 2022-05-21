f-strings is a Python 3.6+ feature, see [1](https://github.com/ShivamSarodia/ShivyC/pull/43/).

```python
import sys
print(f'Your Python version: {sys.version}')
```

```python
import string

print(str.strip.__doc__)

caution = '*** Caution: I am a cat! ***'
print(caution.strip('* '))

print(caution.strip(string.punctuation))
```

```python
tang = '烫烫烫'.encode('cp936')
print(str(tang, 'cp936'))
```

Pad left/right:

https://github.com/astanin/python-tabulate/blob/v0.8.9/tabulate.py#L717

casefold:

[Case insensitive dictionary](https://stackoverflow.com/questions/2082152/case-insensitive-dictionary)

> You should use .casefold() instead of .lower() for comparisons, self.key.casefold() == other.key.casefold(), to allow "ß" and "ss" to equate as true, among others.
