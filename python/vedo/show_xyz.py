# coding: utf-8

import vedo  # pip install vedo -i https://pypi.doubanio.com/simple


def show_xyz(xyz):
    pts = vedo.Points(xyz)
    vedo.show(pts, axes=1, elevation=-30)


def main():
    show_xyz([[0, 0, .5], [0, 1, 0], [1, 0, 0.5], [1, 1, 1]])


if __name__ == '__main__':
    main()

# References:
# https://github.com/marcomusy/vedo/blob/master/examples/notebooks/interpolate_volume.ipynb
