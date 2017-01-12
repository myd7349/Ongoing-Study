from distutils.core import setup
import os.path

from Cython.Build import cythonize


def build_ext(module_name):
    if not isinstance(module_name, str):
        raise ValueError('Excepted a str object')

    pyx_file = module_name+'.pyx'
    if not os.path.isfile(pyx_file):
        raise ValueError('Could not find: {}'.format(pyx_file))

    setup(
        name=module_name,
        ext_modules=cythonize(pyx_file),
        script_args=['build_ext', '--inplace'],
        )


# References:
# cppimport.build_module
