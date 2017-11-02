#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2017-11-02T14:11+08:00

import itertools


def counter(stop=None):
    assert stop is None or isinstance(stop, int)

    count = 0
    
    if stop is None:
        while True:
            yield count
            count = count + 1
    else:
        while count < stop:
            yield count
            count = count + 1


def get_the_n_next_values_of_a_generator():
    # References:
    # https://stackoverflow.com/questions/5234090/how-to-take-the-first-n-items-from-a-generator-or-list-in-python
    # https://stackoverflow.com/questions/4152376/how-to-get-the-n-next-values-of-a-generator-in-a-list-python
    assert list(itertools.islice(counter(), 5)) == [0, 1, 2, 3, 4]
    assert list(itertools.islice(counter(4), 5)) == [0, 1, 2, 3]


if __name__ == '__main__':
    get_the_n_next_values_of_a_generator()
