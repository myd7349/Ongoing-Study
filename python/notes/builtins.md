1. [Allow help() to work on partial function object](https://stackoverflow.com/questions/16672856/allow-help-to-work-on-partial-function-object)
   
   > I found a pretty hacky way to do this. I wrote the following function to override the `__builtins__.help` function:
   > 
   > ```python
   > def partialhelper(object=None):
   >     if isinstance(object, functools.partial):
   >         return pydoc.help(object.func)
   >     else:
   >         # Preserve the ability to go into interactive help if user calls
   >         # help() with no arguments.
   >         if object is None:
   >             return pydoc.help()
   >         else:
   >             return pydoc.help(object)
   > ```
   > 
   > Then just replace it in the REPL with:
   > 
   > ```python
   > __builtins__.help = partialhelper
   > ```

2. open
   
   ```python
   # tokenize.py
   from builtins import open as _builtin_open
   ```


