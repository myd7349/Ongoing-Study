* [How to create a single executable file(.exe) from python code on windows?](https://github.com/myd7349/Ongoing-Study/issues/4)

I used to pack my python code as an executable file with [cx_Freeze](http://cx-freeze.sourceforge.net/). And when all thing was done, I may got a `.exe` file, plus with some `.pyd` and `.dll` files it depends.

The Windows version of official [NydusVPN](http://www.ny-dus.info/) client is written in Python. When I opened `NydusVPN.exe` with `Bandizip`/`7-zip`, I found that all these stuffs are in this "archive": the `.pyc`, `.pyd` and the `.dll` files. WOW! Nice. Can I do the same thing with `cx_Freeze`?

The answer is NO:
[cx_Freeze FAQ - Single-file executables](http://cx-freeze.readthedocs.org/en/latest/faq.html)

> Single-file executables
> 
> cx_Freeze does not support building a single file exe, where all of the libraries for your application are embedded in one executable file.
> 
> You can use IExpress to compress the build directory from cx_Freeze into a self-extracting archive: an exe which unpacks your application into a temporary directory and runs it. IExpress is a utility that’s included with Windows, intended for making installers, but it works equally well if you tell it to run the cx_Freeze-built exe after extraction.
> 
> Alternatively, you can create a self extracting archive using 7zip. This is a bit more complex than using IExpress, but might provide more flexibility, and allows you to build your application using only open source tools.

**Solution 1**: cx_Freeze + [IExpress](http://en.wikipedia.org/wiki/IExpress)

<p></p>

**Solution 2**: cx_Freeze + [UPX](http://upx.sourceforge.net/) <sup>[[1](http://stackoverflow.com/questions/4999567/cx-freeze-python-single-file)]</sup>

<p></p>

**Solution 3**: :star: [py2exe](http://www.py2exe.org/) <sup>[[2](http://stackoverflow.com/questions/112698/py2exe-generate-single-executable-file)]</sup> <sup>[[3](http://stackoverflow.com/questions/1730742/pack-program-and-dynamically-loaded-files-into-single-executable-python-py)]</sup>

<p>py2exe can be used in Python 3.x currently: <a href="http://stackoverflow.com/questions/505230/py2exe-for-python-3-0">py2exe for Python 3.0</a>.</p>

**Solution 4**: :star: [PyInstaller](https://github.com/pyinstaller/pyinstaller/wiki) <sup>[[2](http://stackoverflow.com/questions/112698/py2exe-generate-single-executable-file)]</sup>. You may refer to this tutorial(in chinese): [Python转exe](https://github.com/smartFlash/pySecurity/blob/master/zh-cn/0x4.md)

- [Convert a Python Project to an Executable (.exe) File using Auto PY to EXE](https://python.plainenglish.io/convert-a-python-project-to-an-executable-exe-file-175080da4485)
- [auto-py-to-exe](https://pypi.org/project/auto-py-to-exe/) - A .py to .exe converter using a simple graphical interface and [PyInstaller](https://www.pyinstaller.org/) in Python.

[[Python executables: py2exe or PyInstaller?](https://stackoverflow.com/questions/6235123/python-executables-py2exe-or-pyinstaller)]

This post mentioned `py2app`: [How to Create a Single Windows Executable from a Python and PyGame Project (Summary)](https://irwinkwan.com/2013/04/29/python-executables-pyinstaller-and-a-48-hour-game-design-compo/)


https://github.com/PedramNavid/GooeyPi


* [Python打包exe的王炸-Nuitka](https://zhuanlan.zhihu.com/p/133303836)
* [shiv](https://github.com/linkedin/shiv)
* [PyOxidizer](https://github.com/indygreg/PyOxidizer)

[pex](https://github.com/pantsbuild/pex)

[Shroud](https://github.com/LLNL/shroud/blob/db592d5d72ed61cbebbd1a084230e15b6b0096b4/Makefile#L116-L182) will uses one of:

- pex
- shiv
- nuitka

[briefcase](https://github.com/beeware/briefcase)

[delocate](https://github.com/matthew-brett/delocate) - Find and copy needed dynamic libraries into python wheels.

[The Hitchhiker’s Guide to Packaging](https://the-hitchhikers-guide-to-packaging.readthedocs.io/en/latest/)

[The State of Python Packaging in 2021](https://venthur.de/2021-06-26-python-packaging.html)

