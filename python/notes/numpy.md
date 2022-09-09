##### array vs asarray

[What is the difference between np.array() and np.asarray()?](https://stackoverflow.com/questions/14415741/what-is-the-difference-between-np-array-and-np-asarray)

##### newaxis

[NumPy array slice using None](https://stackoverflow.com/questions/1408311/numpy-array-slice-using-none)

```python
import numpy as np

x = np.linspace(-2, 2, 5)

x
Out[41]: array([-2., -1.,  0.,  1.,  2.])

x[None,:]
Out[42]: array([[-2., -1.,  0.,  1.,  2.]])
```

```python
a = np.array([1,2,3])

a[None,:]
Out[90]: array([[1, 2, 3]])

a[:,None]
Out[91]: 
array([[1],
       [2],
       [3]])
```

[How to fit result of matplotlib.pyplot.contourf into circle?](https://stackoverflow.com/questions/15361143/how-to-fit-result-of-matplotlib-pyplot-contourf-into-circle)

```python
zi = scipy.interpolate.griddata((x, y), z, (xi[None,:], yi[:,None]), method='cubic')
```

##### einsum

[Understanding NumPy's einsum](https://stackoverflow.com/questions/26089893/understanding-numpys-einsum)

https://twitter.com/ArashVahdat/status/1356812244642721794

[MRG: Faster topomaps](https://github.com/mne-tools/mne-python/pull/4224)

```python
def _griddata(x, y, v, xi, yi):
    """Make griddata."""
    xy = x.ravel() + y.ravel() * -1j
    d = xy[None, :] * np.ones((len(xy), 1))
    d = np.abs(d - d.T)
    n = d.shape[0]
    d.flat[::n + 1] = 1.
    g = (d * d) * (np.log(d) - 1.)
    g.flat[::n + 1] = 0.
    weights = linalg.solve(g, v.ravel())

    d = np.abs(xi + -1j * yi - xy[:, np.newaxis, np.newaxis])
    mask = (d == 0)
    d[mask] = 1.
    g = np.log(d)
    g -= 1.
    g *= d * d
    g[mask] = 0.
    zi = np.einsum('i,ijk->jk', weights, g)
    return zi
```

##### ascontiguousarray

[从Numpy中的ascontiguousarray说起](https://zhuanlan.zhihu.com/p/59767914)

[What is the difference between contiguous and non-contiguous arrays?](https://stackoverflow.com/questions/26998223/what-is-the-difference-between-contiguous-and-non-contiguous-arrays)

##### hstack vs vstack

[How do I add an extra column to a NumPy array?](https://stackoverflow.com/questions/8486294/how-do-i-add-an-extra-column-to-a-numpy-array)

```
a = { 0: 0, 1: 1, 2: 2, 3: 3 }

for v in a.values():
    v *= v

a
Out  [9]: {0: 0, 1: 1, 2: 2, 3: 3}

import numpy as np

b = { 0: np.array([0]),  1: np.array([1]), 2: np.array([2]), 3: np.array([3])}

for v in b.values():
    v *= v

b
Out  [13]: {0: array([0]), 1: array([1]), 2: array([4]), 3: array([9])}
```

[Add single element to array in numpy](https://stackoverflow.com/questions/7332841/add-single-element-to-array-in-numpy)

[Numpy - add row to array](https://stackoverflow.com/questions/3881453/numpy-add-row-to-array)

```python
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
```

##### flatten vs ravel

[numpy中的ravel()、flatten()、squeeze()的用法与区别](https://blog.csdn.net/tymatlab/article/details/79009618)

> ravel()：如果没有必要，不会产生源数据的副本
>
> flatten()：返回源数据的副本

##### intp_t

[Difference between np.int, np.int_, int, and np.int_t in cython?](https://stackoverflow.com/questions/21851985/difference-between-np-int-np-int-int-and-np-int-t-in-cython)

##### LAPACK

[Find out if/which BLAS library is used by Numpy](https://stackoverflow.com/questions/37184618/find-out-if-which-blas-library-is-used-by-numpy)

[How to check BLAS/LAPACK linkage in NumPy and SciPy?](https://stackoverflow.com/questions/9000164/how-to-check-blas-lapack-linkage-in-numpy-and-scipy)

[看来，计算速度会根据用于Numpy的BLAS而变化[Python]](https://insilico-notebook.com/zh-CN/python-blas-performance/)

##### reshape(-1, ...)

https://github.com/scipy/scipy/blob/main/scipy/spatial/_qhull.pyx

```python
import numpy as np

a = np.arange(12).reshape(-1, 3)

a
Out[3]: 
array([[ 0,  1,  2],
       [ 3,  4,  5],
       [ 6,  7,  8],
       [ 9, 10, 11]])
```

##### unwrap

https://github.com/scipy/scipy/blob/main/scipy/signal/_spectral_py.py

[Practical Introduction to Frequency-Domain Analysis](https://ch.mathworks.com/help/signal/ug/practical-introduction-to-frequency-domain-analysis.html;jsessionid=8ec6989b9f67b8a1629586db7407)

##### Misc.

https://github.com/llohse/libnpy

https://github.com/rogersce/cnpy

https://github.com/dpilger26/NumCpp

[Make distutils look for numpy header files in the correct place](https://stackoverflow.com/questions/2379898/make-distutils-look-for-numpy-header-files-in-the-correct-place)
