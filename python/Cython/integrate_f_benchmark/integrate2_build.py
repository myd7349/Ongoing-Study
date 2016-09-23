from distutils.core import setup
from Cython.Build import cythonize

import sys
sys.argv.append('build_ext')
sys.argv.append('--inplace')

setup(
	name='integrate2',
	ext_modules=cythonize('integrate2.pyx'),
)
