#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2017-01-09T18:27:41+08:00

# C Interfaces and Implementations
# Exercise 3.1

import distutils.core
import os.path
import string
import sys

import matplotlib.pyplot as plt
import pybind11


def build_c_extension(module_name):
    print(module_name)
    
    ext_modules = [
        distutils.core.Extension(
            module_name,
            ['cii_atom.c', 'cii_atom_pybind11.cpp'],
            include_dirs=[pybind11.get_include(True), pybind11.get_include(False)],
            )
        ]

    sys.argv.append('build_ext')
    sys.argv.append('--inplace')
    distutils.core.setup(name=module_name, ext_modules=ext_modules)
    sys.argv.remove('build_ext')
    sys.argv.remove('--inplace')


def bucket_size_benchmark():
    module_name_template = string.Template('cii_atom_with_bucket_size_$bucket_size')
    config_template = string.Template('\n'.join((
        "#define BUCKET_SIZE $bucket_size",
        "#define CII_ATOM_MODULE $module_name", 
        )))
    
    bucket_size_list = 2048, 2039

    fig = plt.figure("Atom string hashing distribution")
        
    for plot_number, size in enumerate(bucket_size_list):
        module_name = module_name_template.substitute(bucket_size=size)
        
        # Generate config file
        with open('cii_atom_config.h', 'w', encoding='ascii') as f:
            f.write(config_template.substitute(bucket_size=size, module_name=module_name))

        build_c_extension(module_name)

        m = __import__(module_name)

        #for i in range(200000): m.Atom_new_from_int(i)
        with open('wordlist', encoding='utf-8') as f:
            for word in f:
                if word:
                    m.Atom_new_from_string(word)

        buckets_hist = tuple(map(m.Atom_bench_bucket_len, range(m.Atom_bench_buckets_size())))
        plt.subplot(len(bucket_size_list), 1, plot_number+1)
        plt.bar(tuple(range(size)), buckets_hist)
        plt.title('bucket size: {}'.format(size))

    plt.show()


if __name__ == '__main__':
    if not os.path.isfile('wordlist'):
        print('Please download the wordlist from: http://www-personal.umich.edu/~jlawler/wordlist')
        sys.exit(0)
    
    bucket_size_benchmark()


# References:
# [GitHub: pybind/python_example](https://github.com/pybind/python_example)
# Matplotlib documentation
