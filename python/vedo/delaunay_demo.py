# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np
import scipy.spatial
import vedo  # pip install vedo -i https://pypi.doubanio.com/simple


def show_delaunay2d_from_xyz(xyz, mode='xy'):
    pts = vedo.Points(xyz, r=6).c('blue3')

    dly = vedo.delaunay2d(pts, mode=mode).c('w').lc('o').lw(1)
    labels = pts.labels('id').z(0.01)

    vedo.show(pts, labels, dly, __doc__, bg="Mint").close()


def show_delaunay2d_from_xy(xy, mode='xy'):
    xy = np.asarray(xy)
    xyz = np.hstack((xy, np.zeros((xy.shape[0], 1))))
    show_delaunay2d_from_xyz(xyz, mode)


if __name__ == '__main__':
    points = np.array([[0, 0], [0, 1.1], [1, 0], [1, 1]])
    tri = scipy.spatial.Delaunay(points)

    plt.triplot(points[:, 0], points[:, 1], tri.simplices)
    plt.plot(points[:, 0], points[:, 1], 'o')

    show_delaunay2d_from_xy(points, 'scipy')

# References:
# https://github.com/scipy/scipy/pull/377
# https://github.com/marcomusy/vedo/blob/master/examples/basic/delaunay2d.py
# [What is the difference between np.array() and np.asarray()?](https://stackoverflow.com/questions/14415741/what-is-the-difference-between-np-array-and-np-asarray)
# [How do I add an extra column to a NumPy array?](https://stackoverflow.com/questions/8486294/how-do-i-add-an-extra-column-to-a-numpy-array)
