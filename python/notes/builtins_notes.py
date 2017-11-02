#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2017-11-02T14:36+08:00

from itertools_notes import counter
    


def reverse_a_generator():
    # References:
    # https://stackoverflow.com/questions/1561214/python-reverse-generator
    assert list(reversed(list(counter(5)))) == [4, 3, 2, 1, 0]
    assert list(reversed([0, 1, 2, 3])) == [3, 2, 1, 0]
    # It is impossible to reverse a generator like `counter(None)`


if __name__ == '__main__':
    reverse_a_generator()
