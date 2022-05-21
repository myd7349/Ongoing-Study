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

[contextlib.redirect_stdout](https://github.com/tbenthompson/cppimport/blob/a3ac34b575cf586fa762adef7dce1f6c10abcc86/cppimport/build_module.py#L82)

[wurlitzer.py](https://github.com/minrk/wurlitzer/blob/main/wurlitzer.py)

https://github.com/mne-tools/mne-python/blob/main/mne/export/_edf.py

```python
@contextmanager
def _auto_close(fid):
    # try to close the handle no matter what
    try:
        yield fid
    finally:
        try:
            fid.close()
        except Exception:
            pass  # we did our best
```
