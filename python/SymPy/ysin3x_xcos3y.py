#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-04-10T18:05+08:00

import sympy
from sympy.abc import x, y
import sympy.plotting

sympy.init_printing(use_unicode=True)

lhs = y * sympy.sin(3*x)
rhs = x * sympy.cos(3*y)

sympy.plotting.plot_implicit(lhs - rhs, title='ysin3x=xcos3y')
