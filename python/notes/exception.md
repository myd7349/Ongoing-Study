1. `raise ... from`

   > https://github.com/pypa/setuptools/pull/2629/files
   >
   > ```python
   > try:
   >     file, = matching
   > except ValueError:
   >     msg = ('No distribution was found. Ensure that `setup.py` '
   >            'is not empty and that it calls `setup()`.')
   >     raise ValueError(msg) from None
   > ```