#! /usr/bin/env python3
# coding: utf-8

# 2017-11-16T16:32+08:00

import itertools


def counting_sort(data):
    data_min = min(data)
    key = lambda x: x - data_min
    k = max(data) - data_min + 1
    
    count = [0] * k
    for x in data:
        count[key(x)] += 1

    # calculate the starting index for each key:
    total = 0
    for i in range(k):  # i = 0, 1, ... k-1
        oldCount = count[i]
        count[i] = total
        total += oldCount

    # copy to output array, preserving order of inputs with equal keys:
    output = data[:]
    for x in data:
        output[count[key(x)]] = x
        count[key(x)] += 1

    return output


def counting_sort_v2(data):
    data_min = min(data)
    key = lambda x: x - data_min
    k = max(data) - data_min + 1
    
    count = [0] * k
    for x in data:
        count[key(x)] += 1

    count_hist = list(itertools.accumulate(count))

    # copy to output array, not stable:
    output = data[:]
    for x in data:
        output[count_hist[key(x)] - 1] = x
        count_hist[key(x)] -= 1

    return output
    

print(counting_sort([4, 3, 2, 1]))
print(counting_sort([0, 4, 1, 3, 1, 2, 4, 1]))
print(counting_sort([0, -1, 4, 0, 2, -3, 8]))

print(counting_sort_v2([4, 3, 2, 1]))
print(counting_sort_v2([0, 4, 1, 3, 1, 2, 4, 1]))
print(counting_sort_v2([0, -1, 4, 0, 2, -3, 8]))


# References:
# https://en.wikipedia.org/wiki/Counting_sort
# https://www.quora.com/How-do-you-preallocate-space-for-lists-in-Python
# Mastering Algorithms with C, Kyle London, 1999
