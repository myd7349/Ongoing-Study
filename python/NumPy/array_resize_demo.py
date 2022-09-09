# -*- coding: utf-8 -*-

import numpy as np

a = np.arange(12).reshape(3, 4)
print(a)
print(a.flags)

try:
    a.resize(4, 4)
except Exception as ex:
    print(ex)

a2 = np.asarray(a)
print(a2.flags)

a3 = np.array(a)
a3_shape = a3.shape
print(a3.flags)
print(a3)
a3.resize(4, 5)
print(a3)
a3.resize(2,3)
print(a3)
print(a3.shape)
print(a3_shape)
print(a3[:4])
