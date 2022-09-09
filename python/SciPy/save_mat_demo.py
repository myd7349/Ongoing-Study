# -*- coding: utf-8 -*-

import scipy.io

content = """
0,0	0.2 0.4
1,0	0.6 0.8 
2,0	1.0 1.2
3,0	1.4 1.6
4,0	1.8 2.0
"""

mdata = []

for line in content.splitlines():
    if not line:
        continue
    
    line_parts = line.replace(',', ' ').split()
    data = tuple(map(float, line_parts))
    mdata.append(data)

scipy.io.savemat('mdata.mat', {'mdata': mdata})
