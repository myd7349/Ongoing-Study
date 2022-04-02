https://github.com/whtsky/kindle-sdr-cleaner/blob/master/kindle_sdr_cleaner.py

[```pathlib.Path(path).touch()```](https://github.com/triton-inference-server/client/blob/d07efb84f938bce126e4d0a0541629113ffe6d53/src/python/library/build_wheel.py#L46)

https://github.com/cnr-isti-vclab/PyMeshLab/blob/aff7092b77d878c0db708ae8e3be23dba5e3e9fb/pymeshlab/__init__.py#L7

> this_path=str(pathlib.Path(\__file__).parent.absolute())

[Changing file extension in Python](https://stackoverflow.com/questions/2900035/changing-file-extension-in-python)

> ```python
> from pathlib import Path
> p = Path('mysequence.fasta')
> p.rename(p.with_suffix('.aln'))
> ```

[Recursively iterate through all subdirectories using pathlib](https://stackoverflow.com/questions/50714469/recursively-iterate-through-all-subdirectories-using-pathlib)

> ```python
> path = Path("docs")
> for p in path.rglob("*"):
>      print(p.name)
> ```

or:

> ```python
> p = Path('docs')
> for i in p.glob('**/*'):
>      print(i.name)
> ```

[How do you get a directory listing sorted by creation date in python?](https://stackoverflow.com/questions/168409/how-do-you-get-a-directory-listing-sorted-by-creation-date-in-python)

> ```python
> import os
> from pathlib import Path
> 
> paths = sorted(Path(dirpath).iterdir(), key=os.path.getmtime)
> ```

[你应该使用pathlib替代os.path](https://www.dongwm.com/post/use-pathlib/)
