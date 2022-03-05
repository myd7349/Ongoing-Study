#### TextIOWrapper

```python
# tokenize.py

from builtins import open as _builtin_open
from io import TextIOWrapper

def detect_encoding(readline):
    # ......

def open(filename):
    """Open a file in read only mode using the encoding detected by
    detect_encoding().
    """
    buffer = _builtin_open(filename, 'rb')
    try:
        encoding, lines = detect_encoding(buffer.readline)
        buffer.seek(0)
        text = TextIOWrapper(buffer, encoding, line_buffering=True)
        text.mode = 'r'
        return text
    except:
        buffer.close()
        raise
```
