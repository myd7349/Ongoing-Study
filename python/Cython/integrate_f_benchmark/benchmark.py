#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2016-09-23T15:42+08:00

import timeit

# Build these extensions.
import build_ext

build_ext.build_ext('integrate2')
build_ext.build_ext('integrate3')
build_ext.build_ext('integrate4')


print('\n\n')

elapsed_seconds = timeit.timeit('integrate_f(0, 10, int(1e6))', number=10, setup='from integrate import integrate_f')
elapsed_seconds_2 = timeit.timeit('integrate_f(0, 10, int(1e6))', number=10, setup='from integrate2 import integrate_f')
elapsed_seconds_3 = timeit.timeit('integrate_f(0, 10, int(1e6))', number=10, setup='from integrate3 import integrate_f')
elapsed_seconds_4 = timeit.timeit('integrate_f(0, 10, int(1e6))', number=10, setup='from integrate4 import integrate_f')

print("Type of '1e6':", type(1e6))
print('integrate:', elapsed_seconds)
print('integrate2:', elapsed_seconds_2, ', and it gives a {:.2f}x speedup.'.format(elapsed_seconds / elapsed_seconds_2))
print('integrate3:', elapsed_seconds_3, ', and it gives a {:.2f}x speedup.'.format(elapsed_seconds / elapsed_seconds_3))
print('integrate4:', elapsed_seconds_3, ', and it gives a {:.2f}x speedup.'.format(elapsed_seconds / elapsed_seconds_4))


# References:
# [Cython online documentations: Faster code via static typing](http://docs.cython.org/en/latest/src/quickstart/cythonize.html)
