[How to measure elapsed time in Python?](https://stackoverflow.com/questions/7370801/how-to-measure-elapsed-time-in-python)

> ```python
> from timeit import default_timer as timer
> 
> start = timer()
> # ...
> end = timer()
> print(end - start) # Time in seconds, e.g. 5.38091952400282
> ```