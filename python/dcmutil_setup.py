# -*- coding: utf-8 -*-

# 2015-05-29T15:18+08:00

# Create one single executable file from `dcmutil.py`.

from distutils.core import setup
import sys

import py2exe  # http://www.py2exe.org/

sys.argv.append('py2exe')

setup(
    options = {'py2exe': {'bundle_files': 1, 'compressed': True}},
    console = [{'script': 'dcmutil.py'}],
    zipfile = None,
    )

# References:
# https://github.com/myd7349/Ongoing-Study/issues/4
# https://github.com/myd7349/Ongoing-Study/issues/8
