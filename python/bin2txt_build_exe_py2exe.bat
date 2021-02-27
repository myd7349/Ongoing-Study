:: This won't work, and you will get the following error:
:: AttributeError: 'Namespace' object has no attribute 'libname'
:: https://github.com/py2exe/py2exe/issues/68

:: py -m py2exe --bundle-files 1 -c bin2txt.py

:: Instead, you should:
py bin2txt_build_exe_py2exe.py

:: Or
:: py -m py2exe.build_exe -b 1 -c bin2txt.py
