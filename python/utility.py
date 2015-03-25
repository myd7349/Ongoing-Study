#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 2014-10-28T22:20+08:00

'''Some small useful code snippets.'''

import functools
import time

# 2014-10-28 22:20    
def benchmark(times):
    '''A decorator for calculating the execution time of calling a function several times.

    In MATLAB, you can use the "tic" and "toc" command to do similar things.
    A module named "timeit" is also available in Python.'''
    
    assert isinstance(times, int) and times >= 0, 'Please pass a non-negative integer to "times".'
    
    def wrap(func):
        @functools.wraps(func)
        def wrap_again(*args, **kwargs):
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
        return wrap_again
    return wrap

# 2014-10-29 19:14
# 2015-03-25T16:12+08:00 This function is deprecated, think about contextlib.suppress.
def nothrow(func):
    '''A decorator for catching all the unhandled exceptions raised by the decorated function.'''
    @functools.wraps(func)
    def wrap(*args, **kwargs):
        try:
            return func(*args, **kwargs)
        except Exception as e:
            print('Unhandled exception: {!r}'.format(e))
    return wrap


            
