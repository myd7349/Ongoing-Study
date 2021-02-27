# -*- coding: utf-8 -*-

from distutils.core import setup
import os.path
import sys

import py2exe  # http://www.py2exe.org/

if len(sys.argv) == 1:
    sys.argv.append("py2exe")

setup(
    options={
        'py2exe': {
            'bundle_files':
            0,
            'compressed':
            True,
            'dist_dir':
            os.path.join(os.path.dirname(__file__), r'build\bin2txt\py2exe')
        }
    },
    console=[{
        'script': 'bin2txt.py'
    }],
    zipfile=None,
)

# References:
# https://github.com/myd7349/Ongoing-Study/issues/4
# https://github.com/myd7349/Ongoing-Study/issues/8
# [py2exe change application name output](https://stackoverflow.com/questions/22765503/py2exe-change-application-name-output)
# [py2exe change application name output](https://stackoverflow.com/questions/22765503/py2exe-change-application-name-output)
