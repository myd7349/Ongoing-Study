#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-01-04T13:18+08:00

# A Python implementation of Kahan summation algorithm.
# I read about this algorithm on:
# http://stackoverflow.com/questions/2386772/difference-between-float-and-double
# (I read about math.fsum on this page too.)
# For more details of this algorithm, see:
# http://en.wikipedia.org/wiki/Kahan_summation_algorithm

def KahanSum(iterable):
    pass

if __name__ == '__main__':
    # The summation of ten 0.1
    print(.1 + .1 + .1 + .1 + .1 + .1 + .1 + .1 + .1 + .1)
    
    # Now, use math.fsum
    import math
    print(math.fsum([.1] * 10))
    
    # This time, use the function we defined above
    KahanSum([.1] * 10)
