[How can I manually generate a .pyc file from a .py file](https://stackoverflow.com/questions/5607283/how-can-i-manually-generate-a-pyc-file-from-a-py-file)

> You can use `compileall` in the terminal. The following 
> command will go recursively into sub directories and make pyc files for 
> all the python files it finds. The [compileall](https://docs.python.org/2/library/compileall.html) module is part of the python standard library, so you don't need to 
> install anything extra to use it. This works exactly the same way for 
> python2 and python3.
> 
> ```python
> python -m compileall .
> ```

> It's been a while since I last used Python, but I believe you can use [`py_compile`](https://docs.python.org/3/library/py_compile.html#py_compile.compile):
> 
> ```python
> import py_compile
> py_compile.compile("file.py")
> ```
