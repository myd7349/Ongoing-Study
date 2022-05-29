[Understanding NumPy's einsum](https://stackoverflow.com/questions/26089893/understanding-numpys-einsum)

https://twitter.com/ArashVahdat/status/1356812244642721794

https://github.com/llohse/libnpy

https://github.com/rogersce/cnpy

https://github.com/dpilger26/NumCpp

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

[Make distutils look for numpy header files in the correct place](https://stackoverflow.com/questions/2379898/make-distutils-look-for-numpy-header-files-in-the-correct-place)
