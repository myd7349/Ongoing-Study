from distutils.core import setup
from Cython.Build import cythonize

import os.path
import sys


def build_ext(module_name):
    if not isinstance(module_name, str):
        raise ValueError('Excepted a str object')

    pyx_file = module_name+'.pyx'
    if not os.path.isfile(pyx_file):
        raise ValueError('Could not find: {}'.format(pyx_file))

    sys.argv.append('build_ext')
    sys.argv.append('--inplace')

    setup(
        name=module_name,
        ext_modules=cythonize(pyx_file),
        )
