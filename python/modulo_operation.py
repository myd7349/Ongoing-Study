#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-02-28T15:11+08:00

import ctypes
import math
import sys


# 1. Modulo operation in C and C++
# According to [1]:
# Given two positive numbers, a (the dividend) and n (the divisor), a modulo n 
# (abbreviated as a mod n) is the remainder of the Euclidean division of a by n.
#
# When either a or n is negative, the naive definition breaks down and programming 
# languages differ in how these values are defined.
# _______________________________________________________
# |   Standards   | Operator | Results has same sign as |
# |-----------------------------------------------------|
# |  C(ISO 1990)  |     %    |  Implementation-defined  |
# |  C(ISO 1999)  |     %    |          Dividend        |
# | C++(ISO 1998) |     %    |  Implementation-defined  |
# | C++(ISO 2011) |     %    |          Dividend        |
# -------------------------------------------------------
# According to [2]:
# Until C99, the rounding direction of the quotient and the sign of the remainder in 
# the built-in division and remainder operators was implementation-defined if either 
# of the operands was negative, but it was well-defined in div and ldiv.
# According to [1]:
# _______________________________________________________
# |   Standards   | Operator | Results has same sign as |
# |-----------------------------------------------------|
# |  C(ISO 1990)  |    div   |          Dividend        |
# |  C(ISO 1999)  |    div   |          Dividend        |
# | C++(ISO 1998) |    div   |          Dividend        |
# | C++(ISO 2011) |    div   |          Dividend        |
# -------------------------------------------------------
# We can also find a well-defined modulo function in [3]. 

if sys.platform == 'win32':
    libc = ctypes.cdll.msvcrt
else:
    raise NotImplementedError('Not tested yet!')

print(libc.div(-3, 2))


# 2. Modulo operation in Python
# According to [1]:
# ________________________________________
# | Operator  | Results has same sign as |
# ---------------------------------------|
# | %, divmod |          Divisor         |
# | math.fmod |          Dividend        |
# ----------------------------------------
print(-3 % 2)
print(divmod(-3, 2)[1])
print(math.fmod(-3, 2))

# References:
# [1] https://en.wikipedia.org/wiki/Modulo_operation
# [2] http://en.cppreference.com/w/c/numeric/math/div
# [3] C Interfaces and Implementations, Chapter 2