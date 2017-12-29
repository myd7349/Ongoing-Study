2017-01-11T17:11:52+08:00

We can find code below in `build_module.py` of project [cppimport](https://github.com/tbenthompson/cppimport):

```python
@contextlib.contextmanager
def stdchannel_redirected(stdchannel):
    """
    Redirects stdout or stderr to a StringIO object. As of python 3.4, there is a
    standard library contextmanager for this, but backwards compatibility!
    """
    try:
        s = io.StringIO()
        old = getattr(sys, stdchannel)
        setattr(sys, stdchannel, s)
        yield s
    finally:
        setattr(sys, stdchannel, old)
```

With the release of Python 3.4, code above can be replaced by `contextlib.redirect_stdout`/`contextlib.redirect_stderr`.
