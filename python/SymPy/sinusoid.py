#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-04-10T17:48+08:00

import sympy
from sympy.plotting import plot

sympy.init_printing(use_unicode=True)

x = sympy.symbols('x')
y = sympy.sin(x)

plot(y)
plot(sympy.diff(y))
