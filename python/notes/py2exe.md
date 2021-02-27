1. [NameError: name '__file__' is not defined when creating dat2dcm.exe with py2exe.](https://github.com/myd7349/Ongoing-Study/issues/6)

This issue is similar to issue #5: We can use `__file__` when [dat2dcm.py](https://github.com/myd7349/Ongoing-Study/blob/master/python/dat2dcm.py) is running in `IDLE`. However, in a python interpreter that running in 'cmd', using `__file__` causes a `NameError` exception.

**_Solutions:**_
[how can i get the executable's current directory in py2exe?](http://stackoverflow.com/questions/2292703/how-can-i-get-the-executables-current-directory-in-py2exe)
[python NameError: name '__file__' is not defined](http://stackoverflow.com/questions/24140593/python-nameerror-name-file-is-not-defined)
[python NameError: global name '__file__' is not defined](http://stackoverflow.com/questions/16771894/python-nameerror-global-name-file-is-not-defined)

2. [Do not let py2exe generate log file](https://github.com/myd7349/Ongoing-Study/issues/8)

**2015-06-09T19:00+08:00**

We have discussed how to generate a stand alone executable file from a Python script in issue #4. And I created a setup script [dat2dcm_setup.py](https://github.com/myd7349/Ongoing-Study/blob/master/python/dat2dcm_setup.py) for [dat2dcm.py](https://github.com/myd7349/Ongoing-Study/blob/master/python/dat2dcm.py) based on the code snippet under this question: [py2exe - generate single executable file](http://stackoverflow.com/questions/112698/py2exe-generate-single-executable-file):

``` python
from distutils.core import setup
import py2exe, sys, os

sys.argv.append('py2exe')

setup(
    options = {'py2exe': {'bundle_files': 1, 'compressed': True}},
    windows = [{'script': "single.py"}],
    zipfile = None,
)
```

But when I tried to add command line argument parsing ability in `dat2dcm.py` by using `argparse` module this afternoon, I found that nothing is dumped by `argparse` when I executing `dat2dcm.exe -h` from command line prompt. However, if some arguments of invalid format were passed to `dat2dcm.exe`, a message box is popped out to notify that something was wrong and the error message has been dumped into `dat2dcm.log`. After I opened `dat2dcm.log`, guess what? All the stuff is in this log file, including the help message produced by `argparse` module.

So, my question is: how can we let `py2exe` not generate log file for us. And the answer is here: [Py2Exe generate log file](http://stackoverflow.com/questions/20549843/py2exe-generate-log-file)

When it comes to `dat2cm.py`, since `dat2dcm.py` is worked as a **console** application, so what should I do is replacing `windows` keyword with `console` keyword in the setup script. Just like this:

``` python
from distutils.core import setup
import sys

import py2exe

sys.argv.append('py2exe')

setup(
    options = {'py2exe': {'bundle_files': 1, 'compressed': True}},
    console = [{'script': 'dat2dcm.py'}],
    zipfile = None,
    )
```

This page tells us more about how a GUI application created by `py2exe` dumps error messages:
[py2exe error logging](http://www.py2exe.org/index.cgi/StderrLog)

> In order to work around this issue, py2exe redirects the stderr standard channel to a file called app.exe.log where app.exe is the name of the executable created by it. Everything printed to stdout is ignored altogether by redirecting it to a "black hole" object. These redirections take place in py2exe's boot_common.py that contains standard startup code for all aplications created by py2exe. That code also displays the "See the logfile for details" message when the application terminates if anything has been written to the log (which may or may not be desirable). 

Here, `app.exe` is a **GUI** application created by `py2exe`.