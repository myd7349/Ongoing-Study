sys.prefix, sys.base_prefix, sys.exec_prefix, sys.base_exec_prefix
- [Workingenv is dead, long live Virtualenv!](http://www.ianbicking.org/blog/2007/10/workingenv-is-dead-long-live-virtualenv.html)
- [28.3. venv — Creation of virtual environments](https://docs.python.org/3/library/venv.html)
    
    >When a virtual environment is active (i.e., the virtual environment’s Python interpreter is running), the attributes sys.prefix and sys.exec_prefix point to the base directory of the virtual environment, whereas sys.base_prefix and sys.base_exec_prefix point to the non-virtual environment Python installation which was used to create the virtual environment. If a virtual environment is not active, then sys.prefix is the same as sys.base_prefix and sys.exec_prefix is the same as sys.base_exec_prefix (they all point to a non-virtual environment Python installation).

In `virtualenv`, it seems that sys.prefix, sys.exec_prefix, sys.base_prefix, sys.base_exec_prefix all point to the same path.

[sys.stderr](https://github.com/triton-inference-server/client/blob/d07efb84f938bce126e4d0a0541629113ffe6d53/src/python/library/build_wheel.py#L37-L40)

> ```python
> def fail_if(p, msg):
>     if p:
>         print('error: {}'.format(msg), file=sys.stderr)
>         sys.exit(1)
> ```

[Dangers of sys.setdefaultencoding('utf-8')](https://stackoverflow.com/questions/28657010/dangers-of-sys-setdefaultencodingutf-8)

[PEP 686: Make UTF-8 mode default](https://discuss.python.org/t/pep-686-make-utf-8-mode-default/14435)

sys.frozen

[Why use getattr instead of hasattr for sys.frozen?](https://stackoverflow.com/questions/59238237/why-use-getattr-instead-of-hasattr-for-sys-frozen)

https://github.com/python/cpython/blob/main/Lib/multiprocessing/context.py

```python
def freeze_support(self):
    '''Check whether this is a fake forked process in a frozen executable.
    If so then run code specified by commandline and exit.
    '''
    if sys.platform == 'win32' and getattr(sys, 'frozen', False):
        from .spawn import freeze_support
        freeze_support()
```

https://pyinstaller.org/en/v3.3.1/runtime-information.html

> The PyInstaller bootloader adds the name frozen to the sys module.

https://github.com/python/cpython/blob/main/Tools/freeze/freeze.py

https://github.com/python/cpython/blob/main/Python/frozenmain.c

https://mail.python.org/pipermail/python-dev/2013-November/130282.html

sys.byteorder

https://github.com/nodejs/node/blob/main/tools/getendian.py
