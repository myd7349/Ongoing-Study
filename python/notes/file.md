[How we can truncate a file at a given size using Python?](https://www.tutorialspoint.com/How-we-can-truncate-a-file-at-a-given-size-using-Python)

> ```python
> f = open(r'data.dat', 'r+')
> f.truncate(1000)
> print(f.read())
> f.close()
> ```

