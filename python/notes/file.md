[How we can truncate a file at a given size using Python?](https://www.tutorialspoint.com/How-we-can-truncate-a-file-at-a-given-size-using-Python)

> ```python
> f = open(r'data.dat', 'r+')
> f.truncate(1000)
> print(f.read())
> f.close()
> ```

[Iterate blocks of a file](https://github.com/avalentino/hashsum/blob/1bc36e78439ee066626d7875fc4e8ae20f0aa2f8/hashsum.py#L59-L69)

> ```python
> def blockiter(fd, blocksize=io.DEFAULT_BUFFER_SIZE):
>     """Iterate on file-like objects reading blocks of the specified size.
>     The `fd` parameter must be a binary or text file-like object opened
>     for reading.
>     The `blocksize` parameter defaults to `io.DEFAULT_BUFFER_SIZE`.
>     """
>     guard = '' if isinstance(fd, io.TextIOBase) else b''
> 
>     return iter(functools.partial(fd.read, blocksize), guard)
> ```

[ReplaceStringsInFile](https://github.com/abseil/abseil-cpp/blob/20211102.0/create_lts.py)
