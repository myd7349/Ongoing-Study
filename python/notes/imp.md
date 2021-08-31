1. [Automatically inline Python function calls](https://tomforb.es/automatically-inline-python-function-calls/)

   > ```python
   > import sys, imp
   > 
   > class Loader(object):
   >     def __init__(self, module):
   >         self.module = module
   > 
   >     def load_module(self, fullname):
   >         return self.module
   > 
   > class Importer(object):
   >     def find_module(self, fullname, path):
   >         file, pathname, description = imp.find_module(
   >             fullname.split(".")[-1], path)
   >         module_contents = file.read()
   >         # We can now mess around with the module_contents.
   >         # and produce a module object
   >         return Loader(make_module(module_contents))
   > 
   > sys.meta_path.append(Importer())
   > ```

2. https://github.com/tbenthompson/cppimport/blob/stable/cppimport/import_hook.py

   
