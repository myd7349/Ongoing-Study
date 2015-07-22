# coding: utf-8

# 2015-07-12T20:46+08:00

#import datetime
import imghdr
import os
#import re
#from stat import *  # suggested usage from `stat.py`

import dirwalker
#import fileutil


def rename_scshot(oldname):
    pass


def dump_timeline():
    pass


def list_images(root_dir, recursively=True):
    """List all image files under specified directory."""
    return filter(imghdr.what, dirwalker.list_files(root_dir, recursively))


if __name__ == '__main__':
    for file in list_images(os.path.dirname(os.path.dirname(__file__))):
        print(file)


# References:
# [Date and Time Formats](http://www.w3.org/TR/NOTE-datetime)
# [What is the best way to generate a unique and short file name in Java](http://stackoverflow.com/questions/825678/what-is-the-best-way-to-generate-a-unique-and-short-file-name-in-java)
# [How to Generate unique file names in C#](http://stackoverflow.com/questions/4657974/how-to-generate-unique-file-names-in-c-sharp)
