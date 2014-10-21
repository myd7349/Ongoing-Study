#!/usr/bin/env python3

# 2014-10-21 18:12 (UTC+8)

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
import random
import timeit

loops = random.randint(10000, 100000)

def benchmark_list_pop_front():
    s = list(range(loops))
    for i in range(loops):
        s.pop(0)

def benchmark_list_pop_back():
    s = list(range(loops))
    for i in range(loops):
        s.pop(-1)

def benchmark_deque_pop_front():
    q = collections.deque(range(loops))
    for i in range(loops):
        q.popleft()

def benchmark_deque_pop_back():
    q = collections.deque(range(loops))
    for i in range(loops):
        q.pop()

def benchmark_list_push_front():
    s = []
    for i in range(loops):
        s.insert(0, None)

def benchmark_list_push_back():
    s = []
    for i in range(loops):
        s.append(None)

def benchmark_deque_push_front():
    q = collections.deque()
    for i in range(loops):
        q.appendleft(None)

def benchmark_deque_push_back():
    q = collections.deque()
    for i in range(loops):
        q.append(None)

if __name__ == '__main__':
    print(loops, 'loops')
    
    for i in dir():
        item = locals()[i]
        #if isinstance(item, collections.Callable) and i.startswith('benchmark'):
        if hasattr(item, '__call__') and i.startswith('benchmark'):
            print('{}:'.format(i),
                timeit.timeit('{}()'.format(i),
                              setup = 'from __main__ import {}'.format(i),
                              number = 1)
                )
