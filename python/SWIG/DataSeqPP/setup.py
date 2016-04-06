#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2016-04-06T09:57+08:00

from distutils.core import setup, Extension
import os.path
import subprocess
import sys


errorlevel, _ = subprocess.getstatusoutput('swig -help')
if errorlevel != 0:
    sys.stderr.write('Command \'swig\' not found.\n')
    sys.exit(errorlevel)

base_dir = os.path.dirname(__file__)

subprocess.run(['swig', '-c++', '-python', os.path.join(base_dir, 'DataSeqPP.i')])

dataseq_source_file = os.path.join(base_dir,
                                   r'..\..\..\cpp\DLL\DataSequenceV2\DataSeq\DataSeq.cpp')
dataseqpp_source_file = os.path.join(base_dir,
                                     r'..\..\..\cpp\DLL\DataSeqPP\DataSeqPP\DataSeqPP.cpp')
dataseqpp_module = Extension('_dataseqpp',
                           sources=[dataseq_source_file,
                                    dataseqpp_source_file,
                                    'DataSeqPP_wrap.cxx'],
                           )

setup(name = 'dataseqpp',
      version = '0.1',
      description = """Python binding for DataSeqPP""",
      author = 'myd7349',
      author_email = 'myd7349@gmail.com',
      url = 'https://github.com/myd7349/Ongoing-Study/tree/master/python/SWIG/DataSeqPP',
      license = 'PSF license',
      py_modules = ['dataseqpp'],
      ext_modules = [dataseqpp_module],
      )


# References:
# SWIG 3.0 Documentation
# https://docs.python.org/2/distutils/setupscript.html
# https://packaging.python.org/en/latest/distributing/#setup-py
