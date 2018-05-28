#! /usr/bin/env python3
# coding: utf-8

# 2018-05-28T10:38+08:00


def img_to_bytes(fn):
    with open(fn, "rb") as fp:
        return bytearray(fp.read())


# References:
# https://stackoverflow.com/questions/22351254/python-script-to-convert-image-into-byte-array

