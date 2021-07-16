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

