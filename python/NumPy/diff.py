#!/usr/bin/env python3
# coding: utf-8

import timeit

import numpy as np


def yihong0618(arr):
    return [j-i for i, j in zip(a, a[1:])]


def diff(arr):
    arr = np.array(arr)
    return arr[1:] - arr[:-1]


def yihong0618_test(length):
    arr = list(range(length))
    yihong0618(arr)


def diff_test(length):
    arr = list(range(length))
    diff(arr)


def np_diff_test(length):
    arr = list(range(length))
    np.diff(arr)


if __name__ == '__main__':
    a = [1, 3, 5, 10, 19]
    print(yihong0618(a))
    print(diff(a))
    print(np.diff(a))
    print(np.diff(a, prepend=0))

    print()

    print(timeit.timeit(lambda: yihong0618(range(10000000)), number=2))
    print(timeit.timeit(lambda: diff(range(10000000)), number=2))
    print(timeit.timeit(lambda: np.diff(range(10000000)), number=2))
    print(timeit.timeit(lambda: yihong0618(range(100)), number=2000000))
    print(timeit.timeit(lambda: diff(range(100)), number=2000000))
    print(timeit.timeit(lambda: np.diff(range(100)), number=2000000))

    print()

    print(timeit.timeit(lambda: yihong0618_test(10000000), number=2))
    print(timeit.timeit(lambda: diff_test(10000000), number=2))
    print(timeit.timeit(lambda: np_diff_test(10000000), number=2))
    print(timeit.timeit(lambda: yihong0618_test(100), number=2000000))
    print(timeit.timeit(lambda: diff_test(100), number=2000000))
    print(timeit.timeit(lambda: np_diff_test(100), number=2000000))


# References:
# https://github.com/demotu/detecta/blob/master/detecta/detect_peaks.py
# https://twitter.com/yihong0618/status/1514205637906878470
# [Python: Finding differences between elements of a list](https://stackoverflow.com/questions/2400840/python-finding-differences-between-elements-of-a-list)

# Output:
# [2, 2, 5, 9]
# [2 2 5 9]
# [2 2 5 9]
# [1 2 2 5 9]

# 7.199999999984996e-06
# 1.7189738
# 1.7266851000000005
# 1.9366797
# 18.114990400000003
# 24.3331768

# 0.6185411999999957
# 1.7150356000000002
# 1.7204194999999984
# 3.5209529000000046
# 16.192703700000003
# 21.29048490000001
