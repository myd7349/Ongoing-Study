2017-01-06T18:59:33+08:00

pybind11.pdf
>7.9 Pickling support
>Note that only the cPickle module is supported on Python 2.7. The second argument to dumps is also crucial: it selects the pickle protocol version 2, since the older version 1 is not supported. Newer versions are also fine¡ªfor instance, specify -1 to always use the latest available version.

2017-03-21T13:23:42+08:00

Python Documentation
>Extending and Embedding the Python Interpreter
>2.1.1. Adding data and methods to the Basic example
The tp_init slot is exposed in Python as the __init__() method. It is used to initialize an object after it¡¯s created. Unlike the new method, we can¡¯t guarantee that the initializer is called. The initializer isn¡¯t called when unpickling objects and it can be overridden.

[Python multiprocessing PicklingError: Can't pickle <type 'function'>](https://stackoverflow.com/questions/8804830/python-multiprocessing-picklingerror-cant-pickle-type-function)

[hdf5pickle](https://github.com/pv/hdf5pickle)
