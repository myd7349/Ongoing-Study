#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-04-22T10:04+08:00

# ∫e^√xdx = ?
# WolframaAlpha: https://www.wolframalpha.com/input/?i=integrate+of+e%5Esqrt(x)
# Maxima: integrate(e^sqrt(x), x)
# MATLAB MuPAD: int(e^sqrt(x), x)

from sympy import sqrt, log, exp, E, integrate, simplify
from sympy.abc import x

print(integrate(E ** sqrt(x)))


# References:
# Calculus, 7ed, James.Stewart, P521, EXAMPLE 2
# http://docs.sympy.org/latest/modules/functions/elementary.html
