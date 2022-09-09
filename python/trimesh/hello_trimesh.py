# coding: utf-8

import trimesh


def show_mesh():
    # attach to logger so trimesh messages will be printed to console
    trimesh.util.attach_to_log()

    # mesh objects can be created from existing faces and vertex data
    mesh = trimesh.Trimesh(vertices=[[0, 0, 0], [0, 0, 1], [0, 1, 0]],
                           faces=[[0, 1, 2]])

    # by default, Trimesh will do a light processing, which will
    # remove any NaN values and merge vertices that share position
    # if you want to not do this on load, you can pass `process=False`
    mesh = trimesh.Trimesh(vertices=[[0, 0, 0], [0, 0, 1], [0, 1, 0]],
                           faces=[[0, 1, 2]],
                           process=False)
    # preview mesh in an opengl window if you installed pyglet and scipy with pip
    mesh.show()  # pip install pyglet -i https://pypi.doubanio.com/simple


def main():
    show_mesh()


if __name__ == '__main__':
    main()


# References:
# https://github.com/mikedh/trimesh
