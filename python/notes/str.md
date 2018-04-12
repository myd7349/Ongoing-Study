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
