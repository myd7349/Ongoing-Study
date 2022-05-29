Projects that using Python C API to create bindings:

- [DearPyGui](https://github.com/hoffstadt/DearPyGui)
- [pycosat](https://github.com/ContinuumIO/pycosat)
- [python-systemd](https://github.com/systemd/python-systemd)
- [pylzma](https://github.com/fancycode/pylzma)
- [py-simple-audio](https://github.com/hamiltron/py-simple-audio)
- [py_yyjson](https://github.com/TkTech/py_yyjson)
- [pycurl](https://github.com/pycurl/pycurl)
- [PyGLM](https://github.com/Zuzu-Typ/PyGLM)
- [h5py](https://github.com/h5py/h5py/blob/0981eee11b1a3a743a09adae852b062085b415b4/h5py/h5f.pyx#L129-L143)
- [aubio](https://github.com/aubio/aubio/tree/master/python)
- [html5-parser](https://github.com/kovidgoyal/html5-parser)
- [mutf8](https://github.com/TkTech/mutf8)
- [orderbook](https://github.com/bmoscon/orderbook)
- [python-blosc](https://github.com/Blosc/python-blosc)
- [sendmsg](https://github.com/slideinc/sendmsg)
- [bfloat16](https://github.com/GreenWaves-Technologies/bfloat16)
- [winterpy](https://github.com/lilydjwg/winterpy/blob/master/pyso/X.c)
- [jsonnet](https://github.com/google/jsonnet)
- [polysnake](https://github.com/jpakkane/polysnake)
- [multidict](https://github.com/aio-libs/multidict)
- [numpy.fft](https://github.com/numpy/numpy/blob/main/numpy/fft/_pocketfft.c)
- [quicklz](https://github.com/robottwo/quicklz)
- [SciPy](https://github.com/scipy/scipy/blob/main/scipy/spatial/src/distance_wrap.c)
- [moderngl](https://github.com/moderngl/moderngl)
- [LinAlg](https://github.com/netcan/LinAlg)
  - [从头开始实现一个线性代数库：Python 模块篇](https://netcan.github.io/2018/05/29/%E4%BB%8E%E5%A4%B4%E5%BC%80%E5%A7%8B%E5%AE%9E%E7%8E%B0%E4%B8%80%E4%B8%AA%E7%BA%BF%E6%80%A7%E4%BB%A3%E6%95%B0%E5%BA%93%EF%BC%9APython%E6%A8%A1%E5%9D%97%E7%AF%87/)
- [BioSig](https://biosig.sourceforge.net/index.html)

Books:

- Python 源码剖析

- CPython Internals: Your Guide to the Python 3 Interpreter

  - https://github.com/tonybaloney/cpython-book-samples

Articles:

- [How can I manually generate a .pyc file from a .py file](https://stackoverflow.com/questions/5607283/how-can-i-manually-generate-a-pyc-file-from-a-py-file)

> You can use `compileall` in the terminal. The following 
> command will go recursively into sub directories and make pyc files for 
> all the python files it finds. The [compileall](https://docs.python.org/2/library/compileall.html) module is part of the python standard library, so you don't need to 
> install anything extra to use it. This works exactly the same way for 
> python2 and python3.
> 
> ```python
> python -m compileall .
> ```

[devguide](https://github.com/python/devguide)

[Make distutils look for numpy header files in the correct place](https://stackoverflow.com/questions/2379898/make-distutils-look-for-numpy-header-files-in-the-correct-place)
