#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2017-04-23T19:24:08+08:00

import platform

pyimpl = platform.python_implementation()

print("Python implementation:", pyimpl)
print('Are you using CPython?', pyimpl == 'CPython')
# https://github.com/jab/bidict/blob/master/bidict/compat.py
print('Are you using PyPy?', pyimpl == 'PyPy')
