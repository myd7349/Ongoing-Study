[What does the Ellipsis object do?](https://stackoverflow.com/questions/772124/what-does-the-ellipsis-object-do)

[What does "three dots" in Python mean when indexing what looks like a number?](https://stackoverflow.com/questions/42190783/what-does-three-dots-in-python-mean-when-indexing-what-looks-like-a-number)

[pyparsing/fourFn.py at ea98f63a4725d3147d7dc6ed7edc40eb7b8f5c80 · pyparsing/pyparsing · GitHub](https://github.com/pyparsing/pyparsing/blob/ea98f63a4725d3147d7dc6ed7edc40eb7b8f5c80/examples/fourFn.py#L91)

[What is the use of Ellipsis in Python?](https://stackoverflow.com/questions/60370908/what-is-the-use-of-ellipsis-in-python)

> ```python
> def do_foo():
>     pass
> ```
> 
> versus
> 
> ```python
> def do_foo():
>     ...
> ```

[How do you use the ellipsis slicing syntax in Python?](https://stackoverflow.com/questions/118370/how-do-you-use-the-ellipsis-slicing-syntax-in-python)

> ```python
> >>> from numpy import arange
> >>> a = arange(16).reshape(2,2,2,2)
> ```
> 
> Now, you have a 4-dimensional matrix of order 2x2x2x2. To select all 
> first elements in the 4th dimension, you can use the ellipsis notation
> 
> ```python
> >>> a[..., 0].flatten()
> array([ 0,  2,  4,  6,  8, 10, 12, 14])
> ```
> 
> which is equivalent to
> 
> ```python
> >>> a[:,:,:,0].flatten()
> array([ 0,  2,  4,  6,  8, 10, 12, 14])
> ```
> 
> In your own implementations, you're free to ignore the contract mentioned above and use it for whatever you see fit.
