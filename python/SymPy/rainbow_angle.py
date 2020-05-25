#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sympy
from sympy.abc import a

# Index of refraction for water: 4/3
k = sympy.Rational(4, 3)
# Snell's law: sin(a) = k*sin(b)
b = sympy.asin(sympy.sin(a) / k)

angle_of_deviation = (a - b) + (sympy.pi - 2 * b) + (a - b)
angle_of_deviation = sympy.simplify(angle_of_deviation)
print(angle_of_deviation)

one_order_diff = sympy.diff(angle_of_deviation)
print(one_order_diff)

radians = sympy.solve(one_order_diff)
print(radians)

angles = [radian / sympy.pi * 180 for radian in radians]
print(angles)

for angle in angles:
    print(angle.evalf())


# References:
# Calculus, 7ed, James.Stewart, P206
# https://docs.sympy.org/latest/modules/evalf.html
# https://docs.sympy.org/0.7.1/modules/mpmath/functions/constants.html#pi-pi
# https://stackoverflow.com/questions/21569792/how-to-find-the-maximum-value-of-a-function-in-sympy
