#! /usr/bin/env python3
# coding: utf-8
# 2014-06-11T23:14+08:00

import sys
import sysconfig
import warnings

if __name__ == '__main__':
    print(type(sys.version_info))
    
    if sys.version_info.major != 2:
        warnings.warn('Need Python 2.x for this program to run.')

    if sys.version_info <= (3, 5):
        print('Need Python 3.5 or newer to run this program.')

    if sys.version.startswith('3'):
        print('You are using Python 3.x!')
    elif sys.version.startswith('2'):
        print('Oh! You are using Python 2.x!')
        
    print(sys.version)
    print(sysconfig.get_python_version())

# References:
# https://github.com/myd7349/Ongoing-Study/issues/3