[What encoding does the "exec" function assume?](https://stackoverflow.com/questions/30621772/what-encoding-does-the-exec-function-assume)

[What is an alternative to execfile in Python 3?](https://stackoverflow.com/questions/436198/what-is-an-alternative-to-execfile-in-python-3)

> ```python
> with open("somefile.py") as f:
>     code = compile(f.read(), "somefile.py", 'exec')
>     exec(code, global_vars, local_vars)
> ```

> `open("somefile.py")` may be incorrect if `somefile.py` uses a character encoding different from `locale.getpreferredencoding()`. `tokenize.open()` could be used instead.

Suppose I have a Python script named `hello.py`:

```python
#!/usr/bin/env python3
# coding: utf-8

print('你好，世界！')

# 参考文献：
# [HDF5 数据文件简介](https://zhuanlan.zhihu.com/p/104145585)
```

then:

```
>> f = open('hello.py')
>>> exec(f.read())
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
UnicodeDecodeError: 'gbk' codec can't decode byte 0x80 in position 80: illegal multibyte sequence
```

Can Python 2.x's `execfile` handle this correctly?

[Run a Python script from another Python script, passing in arguments [duplicate]](https://stackoverflow.com/questions/3781851/run-a-python-script-from-another-python-script-passing-in-arguments)

[Alternative to execfile in Python 3? [duplicate]](https://stackoverflow.com/questions/6357361/alternative-to-execfile-in-python-3)

> ```python
> exec(compile(open('hello.py', "rb").read(), filename, 'exec'), globals, locals)
> ```

[Alternative to execfile in Python 3?](https://stackoverflow.com/questions/6357361/alternative-to-execfile-in-python-3)

> Uses binary reading to avoid encoding issues.

> ```python
> def exec_full(filepath):
>     global_namespace = {
>         "__file__": filepath,
>         "__name__": "__main__",
>     }
>     with open(filepath, 'rb') as file:
>         exec(compile(file.read(), filepath, 'exec'), global_namespace)
> 
> # Execute the file.
> exec_full("/path/to/somefile.py")
> ```

```python
import tokenize

def execfile(fn):
    f = tokenize.open(fn)
    exec(f.read())
```

[What's the difference between eval, exec, and compile?](https://stackoverflow.com/questions/2220699/whats-the-difference-between-eval-exec-and-compile)

> `exec` and `eval` both accept the program/expression to be run either as a `str`, `unicode` or `bytes` object containing source code, or as a *`code` object* which contains Python bytecode.
> 
> If a `str`/`unicode`/`bytes` containing source code was passed to `exec`, it behaves equivalently to:
> 
> ```python
> exec(compile(source, '<string>', 'exec'))
> ```
