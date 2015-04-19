#! /usr/bin/env python3
# coding: utf-8
# 2014-07-01T21:54+08:00

import time

count = 1000000

def countdown(n):
    def next():
        nonlocal n
        r = n
        n -= 1
        return r
    return next

class Countdown(object):
    def __init__(self, n):
        self.__n = n
    def next(self):
        r = self.__n
        self.__n -= 1
        return r

# test case #1
start = time.time()

next = countdown(count)
while True:
    v = next()
    if not v: break

end = time.time()

print('Test case #1: {:f} seconds'.format(end - start))

# test case #2
start = time.time()

c = Countdown(count)
while True:
    v = c.next()
    if not v: break
    
end = time.time()

print('Test case #2: {:f} seconds'.format(end - start))
