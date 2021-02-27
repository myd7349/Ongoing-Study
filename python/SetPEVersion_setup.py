# -*- coding: utf-8 -*-

from distutils.core import setup
import sys

import py2exe  # http://www.py2exe.org/

sys.argv.append('py2exe')

setup(
    options = {'py2exe': {'bundle_files': 1, 'compressed': True}},
    console = [{'script': 'SetPEVersion.py'}],
    zipfile = None,
    )
