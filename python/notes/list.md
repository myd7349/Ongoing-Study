2017-11-16T16:17+08:00

Q: How to preallocate space for lists in Python?
A: https://www.quora.com/How-do-you-preallocate-space-for-lists-in-Python

```
You can create a list of preallocated length SIZE with an initial value (e.g. 0) by doing this:

    x = [0] * SIZE
```

Example:

[counting sort](https://en.wikipedia.org/wiki/Counting_sort) implemented with Python: [counting_sort.py](../../algorithm/sort/counting_sort.py)
