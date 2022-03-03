[What is an alternative to execfile in Python 3?](https://stackoverflow.com/questions/436198/what-is-an-alternative-to-execfile-in-python-3)

> `open("somefile.py")` may be incorrect if `somefile.py` uses a character encoding different from `locale.getpreferredencoding()`. `tokenize.open()` could be used instead.
