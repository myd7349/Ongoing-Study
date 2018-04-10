#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-04-10T20:13+08:00

import sympy
from sympy.abc import x, y

eq = x**4 + y**4 - 16  # x^4 + y^4 = 16
second_order_idiff = sympy.idiff(eq, y, x, n=2)

print(second_order_idiff)
print(second_order_idiff.simplify())


# References:
# Calculus, 7ed, James.Stewart, P161