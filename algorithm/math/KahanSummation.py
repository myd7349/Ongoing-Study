#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-01-04T13:18+08:00

# A Python implementation of Kahan summation algorithm.
# I read about this algorithm on:
# http://stackoverflow.com/questions/2386772/difference-between-float-and-double
# (I read about math.fsum on this page too.)
# For more details of this algorithm, see:
# http://en.wikipedia.org/wiki/Kahan_summation_algorithm
# The doc of math.fsum in Python 3.4.2 documentation also mention this page:
# ASPN cookbook recipes for accurate floating point summation: http://code.activestate.com/recipes/393090/

# 2015-07-27T13:51+08:00
# Ongoing-Study/cpp/Boost/Accumulators/KahanSum


def KahanSum(iterable):
    res = 0.0
    
    # A running compensation for lost low-order bits.
    compensation = 0.0

    for elem in iterable:
        # So far, so good; compensation is zero.
        y = elem - compensation
        # Alas, res is big, y small, so low-order digits of y are lost.
        t = res + y
        # (t - res) recovers the high-order part of y; subtracting y recovers -(low part of y)
        compensation = (t - res) - y
        # Algebraically, compensation should always be zero. Beware overly-aggressive optimizing compilers!
        res = t
        # Next time around, the lost low part will be added to y in a fresh attempt.

    return res


if __name__ == '__main__':
    # The summation of ten 0.1
    #print(.1 + .1 + .1 + .1 + .1 + .1 + .1 + .1 + .1 + .1)
    print(sum([.1] * 10))

    # Now, use math.fsum
    import math
    print(math.fsum([.1] * 10))

    # This time, use the function we defined above
    print(KahanSum([.1] * 10))

#### Output(Tested on Win7 x64):
## Python 2.7.8:
#1.0
#1.0
#1.0
## Python 3.4.2:
#0.9999999999999999
#1.0
#1.0
