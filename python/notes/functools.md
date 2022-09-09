1. lru_cache
   
   - [pdm](https://github.com/pdm-project/pdm/blob/main/src/pdm/installers/installers.py)
   - [wurlitzer.py](https://github.com/minrk/wurlitzer/blob/7ce0c19442248049fc59db6a8e98d54d9a13b73f/wurlitzer.py#L119)
   - [scipy/fft/\_helper.py](https://github.com/scipy/scipy/blob/v1.9.0/scipy/fft/_helper.py)

2. [Allow help() to work on partial function object](https://stackoverflow.com/questions/16672856/allow-help-to-work-on-partial-function-object)
   
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


