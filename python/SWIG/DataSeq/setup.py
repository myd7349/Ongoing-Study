#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2016-04-02T00:22+08:00

from distutils.core import setup, Extension
import os.path
import subprocess
import sys


errorlevel, _ = subprocess.getstatusoutput('swig -help')
if errorlevel != 0:
    sys.stderr.write('Command \'swig\' not found.\n')
    sys.exit(errorlevel)

subprocess.run(['swig', '-python', 'DataSeq.i'])

dataseq_source_file = os.path.join(os.path.dirname(__file__),
                                   r'..\..\..\cpp\DLL\DataSequenceV2\DataSeq\DataSeq.cpp')
dataseq_module = Extension('_dataseq',
                           sources=[dataseq_source_file, 'DataSeq_wrap.c'],
                           )

setup(name = 'dataseq',
      version = '0.3',
      author = "myd7349",
      description = """Python binding for DataSeq""",
      ext_modules = [dataseq_module],
      py_modules = ["dataseq"],
      )


# References:
# SWIG 3.0 Documentation
