#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 2014-10-28 22:20 (UTC+8)

'''Some small useful code snippets.'''

import functools
import time
    
def benchmark(times):
    '''A decorator for calculating the execution time of calling a function several times.

    In MATLAB, you can use the "tic" and "toc" command to do similar things.
    A module named "timeit" is also available in Python.'''
    
    def wrapper(func):
        @functools.wraps(func)
        def another_wrapper(*args, **kwargs):
            # *** The documentation says that time.clock() is deprecated in Python 3.3.
            start = time.clock()
            for i in range(times):
                res = func(*args, **kwargs)
            end = time.clock()

            print('------------------------------------- tic -------------------------------------')
            print('Run "{}" for {} time{}'.format(func.__name__, times,
                                              's' if times != 1 else ''))
            print('Time totally used: {} s'.format(end - start))
            print('------------------------------------- toc -------------------------------------')

            return res    
        return another_wrapper
    return wrapper
