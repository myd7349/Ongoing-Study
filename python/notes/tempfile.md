https://github.com/fatiando/pooch/blob/v1.6.0/pooch/utils.py#L267-L296

```python
@contextmanager
def temporary_file(path=None):
    """
    Create a closed and named temporary file and make sure it's cleaned up.
    Using :class:`tempfile.NamedTemporaryFile` will fail on Windows if trying
    to open the file a second time (when passing its name to Pooch function,
    for example). This context manager creates the file, closes it, yields the
    file path, and makes sure it's deleted in the end.
    Parameters
    ----------
    path : str or PathLike
        The directory in which the temporary file will be created.
    Yields
    ------
    fname : str
        The path to the temporary file.
    """
    tmp = tempfile.NamedTemporaryFile(delete=False, dir=path)
    # Close the temp file so that it can be opened elsewhere
    tmp.close()
    try:
        yield tmp.name
    finally:
        if os.path.exists(tmp.name):
            os.remove(tmp.name)
```
