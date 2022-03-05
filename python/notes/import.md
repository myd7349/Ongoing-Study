[Python: importing a sub‑package or sub‑module](https://stackoverflow.com/questions/12229580/python-importing-a-sub-package-or-sub-module)

[Can you hide imported modules from a sub package in python?](https://stackoverflow.com/questions/63229633/can-you-hide-imported-modules-from-a-sub-package-in-python)

https://github.com/uvemas/ViTables/blob/b6f1a8164f56d793f1f4f8cc4132c4cd9af8c374/vitables/vtapp.py#L1249

> 'NumPy': tables.numpy.\_\_version__,

[Use `import numpy as np` everywhere by eumiro · Pull Request #864 · PyTables/PyTables · GitHub](https://github.com/PyTables/PyTables/pull/864)

So:

> 'NumPy': tables.numpy.\_\_version__,

doesn't work anymore. Change this to:

> 'NumPy': tables.np.\_\_version__,
