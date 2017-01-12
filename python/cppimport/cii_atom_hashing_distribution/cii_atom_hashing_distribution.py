#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2017-01-12T12:23:35+08:00

# C Interfaces and Implementations
# Exercise 3.1

import os
import os.path
import sys

import cppimport
import matplotlib.pyplot as plt


same_dir = lambda entry: os.path.join(os.path.dirname(__file__), entry)

sys.path.append(os.getcwd())


def bucket_size_benchmark():
    #bucket_sizes = 2048, 2039
    bucket_sizes = (2039, )

    fig = plt.figure("Atom string hashing distribution")

    for plot_number, size in enumerate(bucket_sizes):
        m = cppimport.imp('cii_atom_cppimport')

        with open(same_dir('wordlist'), encoding='utf-8') as f:
            for word in f:
                word = word.strip()
                if word:
                    m.Atom_new_from_string(word)

        buckets_hist = tuple(map(m.Atom_bench_bucket_len, range(m.Atom_bench_buckets_size())))
        plt.subplot(len(bucket_sizes), 1, plot_number+1)
        plt.bar(tuple(range(size)), buckets_hist)
        plt.title('bucket size: {}'.format(size))

    plt.show()


if __name__ == '__main__':
    if not os.path.isfile(same_dir('wordlist')):
        print('Please download the wordlist from: http://www-personal.umich.edu/~jlawler/wordlist')
        sys.exit(0)
    
    bucket_size_benchmark()


# References:
# [GitHub: pybind/python_example](https://github.com/pybind/python_example)
# Matplotlib documentation
