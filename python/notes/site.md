[Introducing the BrainVision LSL Viewer](https://pressrelease.brainproducts.com/lsl-viewer/)

D:\Program Files\BrainVision LSL Viewer\RunLSLViewer.py

```python
'''
------------------------------------------------------------

Copyright (C) 2020, Brain Products GmbH, Gilching

This file is part of BrainVision LSL Viewer

BrainVision LSL Viewer is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 3
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with PyCorder. If not, see <http://www.gnu.org/licenses/>.

------------------------------------------------------------

@author: Norbert Hauser
@date: 23.03.2020
@version: 1.0
'''

import sys, os
import site

curdir = os.path.dirname(os.path.abspath(__file__))
pkgdir = os.path.join(curdir, 'pkgs')
sys.path.insert(0, os.path.join(curdir, 'pkgs', 'LSL_Viewer'))

# Ensure .pth files in pkgdir are handled properly
site.addsitedir(pkgdir)
os.environ['PYTHONPATH'] = pkgdir + os.pathsep + os.environ.get('PYTHONPATH', '')

from base.main import main

main(sys.argv)
```
