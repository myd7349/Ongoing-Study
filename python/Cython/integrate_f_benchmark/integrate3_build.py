from distutils.core import setup
from Cython.Build import cythonize

import sys
sys.argv.append('build_ext')
sys.argv.append('--inplace')


setup(
	name='integrate3',
	ext_modules=cythonize('integrate3.pyx'),
)
