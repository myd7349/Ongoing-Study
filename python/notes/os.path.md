1. Copy a directory recursively

   > \# https://github.com/triton-inference-server/client/blob/d07efb84f938bce126e4d0a0541629113ffe6d53/src/python/library/build_wheel.py#L51-L66
   >
   > from distutils.dir_util import copy_tree
   
2. [How do you get a directory listing sorted by creation date in python?](https://stackoverflow.com/questions/168409/how-do-you-get-a-directory-listing-sorted-by-creation-date-in-python)

   > ```python
   > import os
   > from pathlib import Path
   > 
   > paths = sorted(Path(dirpath).iterdir(), key=os.path.getmtime)
   > ```

3. [which](https://github.com/Z3Prover/z3/blob/z3-4.8.15/scripts/mk_util.py#L176-L191)

4. expanduser

```python
# https://susam.net/blog/import-readline.html
HISTORY_FILE = os.path.expanduser('~/.repl_history')
```
