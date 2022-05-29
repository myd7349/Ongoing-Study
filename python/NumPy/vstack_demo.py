#!/usr/bin/env python3
# coding: utf-8


import numpy as np

arr = np.identity(3)
print(arr)

# Output:
# [[1. 0. 0.]
#  [0. 1. 0.]
#  [0. 0. 1.]]

arr2 = np.append(arr, [1, 2, 3])
print(arr2)

# Output:
# [1. 0. 0. 0. 1. 0. 0. 0. 1. 1. 2. 3.]

print(arr)

# Output:
# [[1. 0. 0.]
#  [0. 1. 0.]
#  [0. 0. 1.]]

arr3 = np.vstack([arr, [1, 2, 3]])
print(arr3)

# Output:
# [[1. 0. 0.]
#  [0. 1. 0.]
#  [0. 0. 1.]
#  [1. 2. 3.]]

# References:
# [Numpy - add row to array](https://stackoverflow.com/questions/3881453/numpy-add-row-to-array)
