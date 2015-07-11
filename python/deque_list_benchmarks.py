#!/usr/bin/env python3

# 2014-10-21T18:12+08:00

"""
Benchmark test for list & deque in Python.

This program is inspired by a question on zhihu.com: 
http://www.zhihu.com/question/26091467

Some more useful information:
http://stackoverflow.com/questions/23487307/python-deque-vs-list-performance-comparison
http://stackoverflow.com/questions/1296511/efficiency-of-using-a-python-list-as-a-queue

C++ benchmark test:
http://baptiste-wicht.com/posts/2012/12/cpp-benchmark-vector-list-deque.html
http://blog.davidecoppola.com/2014/05/20/cpp-benchmarks-vector-vs-list-vs-deque/
http://stackoverflow.com/questions/1436020/c-stl-containers-whats-the-difference-between-deque-and-list
"""

import collections
#import inspect
import random
import timeit
#import types

loops = random.randint(10000, 100000)
rng = range(loops)

def benchmark_list_pop_front():
    s = list(rng)
    for i in rng:
        s.pop(0)

def benchmark_list_pop_back():
    s = list(rng)
    for i in rng:
        s.pop(-1)

def benchmark_deque_pop_front():
    q = collections.deque(rng)
    for i in rng:
        q.popleft()

def benchmark_deque_pop_back():
    q = collections.deque(rng)
    for i in rng:
        q.pop()

def benchmark_list_push_front():
    s = []
    for i in rng:
        s.insert(0, None)

def benchmark_list_push_back():
    s = []
    for i in rng:
        s.append(None)

def benchmark_deque_push_front():
    q = collections.deque()
    for i in rng:
        q.appendleft(None)

def benchmark_deque_push_back():
    q = collections.deque()
    for i in rng:
        q.append(None)

if __name__ == '__main__':
    print(loops, 'loops')
    
    for i in dir():
        item = locals()[i]

        # Several ways to check whether an object is callable or not.
        #  0. unittest.mock defines two internal function: _callable, _instance_callable
        #  1. if isinstance(item, collections.Callable) and i.startswith('benchmark'):
        #  2. if isinstance(item, types.FunctionType) and i.startswith('benchmark'):
        #  3. if inspect.isfunction(item) and i.startswith('benchmark'):
        #  4. 
        if hasattr(item, '__call__') and i.startswith('benchmark'):
            print('{}:'.format(i),
                timeit.timeit('{}()'.format(i),
                              setup = 'from __main__ import {}'.format(i),
                              number = 1)
                )
