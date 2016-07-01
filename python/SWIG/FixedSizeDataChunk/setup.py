#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2016-07-01T15:41+08:00

from distutils.core import setup, Extension
import os.path
import subprocess
import sys


errorlevel, _ = subprocess.getstatusoutput('swig -help')
if errorlevel != 0:
    sys.stderr.write('Command \'swig\' not found.\n')
    sys.exit(errorlevel)

base_dir = os.path.dirname(__file__)
subprocess.run(['swig', '-c++', '-python', os.path.join(base_dir, 'FixedSizeDataChunk.i')])

fixedsizedatachunk_module = Extension('_fixedsizedatachunk', sources=['FixedSizeDataChunk_wrap.cxx'])

setup(name = 'fixedsizedatachunk',
      version = '0.1',
      description = """Python binding for std::array<unsigned char, 1024>""",
      author = 'myd7349',
      author_email = 'myd7349@gmail.com',
      url = 'https://github.com/myd7349/Ongoing-Study/tree/master/python/SWIG/FixedSizeDataChunk',
      license = 'PSF license',
      py_modules = ['fixedsizedatachunk'],
      ext_modules = [fixedsizedatachunk_module],
      )
