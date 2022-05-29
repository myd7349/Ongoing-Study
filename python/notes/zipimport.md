[Python Zip Imports: Distribute Modules and Packages Quickly](https://realpython.com/python-zip-import/)

https://docs.python.org/3/library/zipimport.html

> Any files may be present in the ZIP archive, but importers are only invoked for .py and .pyc files. ZIP import of dynamic modules (.pyd, .so) is disallowed. Note that if an archive only contains .py files, Python will not attempt to modify the archive by adding the corresponding .pyc file, meaning that if a ZIP archive doesn’t contain .pyc files, importing may be rather slow.
