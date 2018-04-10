#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-04-10T17:48+08:00

import sympy
from sympy.abc import x, y
import sympy.plotting

sympy.init_printing(use_unicode=True)

lhs = x ** 3 + y ** 3
rhs = 6 * x * y
folium = sympy.Eq(lhs, rhs)

title = 'Folium of Descartes'

sympy.plotting.plot_implicit(folium, title=title)

folium = lhs - rhs
folium_idiff = sympy.idiff(folium, y, x).simplify()
print(folium_idiff)
sympy.plotting.plot_implicit(folium_idiff, title=str(folium_idiff))


# References:
# Calculus, 7ed, James.Stewart, P157
# https://stackoverflow.com/questions/35390187/using-sympy-equations-for-plotting
# https://stackoverflow.com/questions/25791425/plot-with-sympy-in-python-3
