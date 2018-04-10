#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-04-10T17:48+08:00

from sympy import Rational as R
from sympy.abc import x, y
from sympy.plotting import plot_implicit

# x^2 + y^2 = (2*x^2 + 2*y^2 - x)^2
plot_implicit(x**2 + y**2 - (2*x**2 + 2*y**2 - x) ** 2, (x, -0.5, 1.5), (y, -0.75, 0.75), title='cardioid')

# x^(2/3) + y^(2/3) = 4
plot_implicit(x**R(2, 3) + y**R(2, 3) - 4, (x, -10, 10), (y, -10, 10), title='astroid')

# 2*(x^2 + y^2)^2 = 25*(x^2 - y^2)
plot_implicit(2 * (x**2 + y**2) ** 2 - 25 * (x**2 - y**2), title='lemniscate')

# y^2*(y^2 - 4) = x^2*(x^2 - 5)
plot_implicit(y ** 2 * (y**2 - 4) - x ** 2 * (x**2 - 5), title='devil\'s curve')

# References:
# Calculus, 7ed, James.Stewart, P157
