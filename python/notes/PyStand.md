[程序路径不能包含中文 · Issue #6 · skywind3000/PyStand · GitHub](https://github.com/skywind3000/PyStand/issues/6)

[示例程序在win7上无法运行 · Issue #7 · skywind3000/PyStand · GitHub](https://github.com/skywind3000/PyStand/issues/7)

- [ImportError: DLL load failed while importing _ctypes: The parameter is incorrect · Issue #3332 · streamlink/streamlink · GitHub](https://github.com/streamlink/streamlink/issues/3332)
  
  > You should use Windows 7 with at least Service Pack 2 installed.  
  > Yes, there's a Service Pack 2 but it's called with a different name: [answers.microsoft.com/en-us/windows/forum/windows_7-update/how-to-obtain-and-install-windows-7-sp2/c2c7009f-3a10-4199-9c89-48e1e883051e](https://answers.microsoft.com/en-us/windows/forum/windows_7-update/how-to-obtain-and-install-windows-7-sp2/c2c7009f-3a10-4199-9c89-48e1e883051e)
  > 
  > [en.wikipedia.org/wiki/Windows_7#Convenience_rollup](https://en.wikipedia.org/wiki/Windows_7#Convenience_rollup)

- [cx_Freeze ImportError: DLL load failed failed while importing _ctypes: The specified module could not be found](https://stackoverflow.com/questions/58953290/cx-freeze-importerror-dll-load-failed-failed-while-importing-ctypes-the-speci)

- [official embedded Python fails to import certain modules](https://bugs.python.org/issue42339)
  
  [python/cpython#23322 (files)](https://github.com/python/cpython/pull/23322/files)
  
  > When running on Windows 7, Python 3.8 requires the KB2533623 update to be installed. The embeddable distribution does not detect this update, and may fail at runtime. Later versions of Windows include this update.

[ViTables](https://github.com/uvemas/ViTables) + PyStand:

> 1. Download embeded python
> 
> 2. install [pip](https://pip.pypa.io/en/stable/installation/)
>    
>    [pip with embedded python - Stack Overflow](https://stackoverflow.com/questions/42666121/pip-with-embedded-python)
>    
>    Note: you should uncomment the following line in `python38._pth`:
>    
>    ```python
>    import site
>    ```
> 
> 3. install `ViTables` requirements:
>    
>    ```
>    python -m pip install -r requirements.txt
>    ```
> 
> 4. Modify `PyStand.int`:
>    
>    ```python
>    #import os
>    
>    from PyQt5.QtCore import *
>    
>    #os.MessageBox(QTextCodec.codecForLocale().name())
>    #os.MessageBox('Qt5 Plugins path: {0}'.format(QLibraryInfo.location(QLibraryInfo.PluginsPath)))
>    #os.environ['QT_QPA_PLATFORM_PLUGIN_PATH'] = r'.\site-packages\PyQt5\Qt5\plugins'
>    
>    QCoreApplication.addLibraryPath(r'.\site-packages\PyQt5\Qt5\plugins')
>    
>    #import vitables
>    
>    from vitables.start import gui
>    gui() 
>    ```
> 
> 5. Clean
