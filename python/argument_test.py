#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 2014-12-18T15:34+08:00

# Python >> 3.4.2 Documentation >> Python Frequently Asked Questions
# What is the difference between arguments and parameters?

# Python glossary: argument
# A value passed to a function (or method) when calling the function.
# There are two kinds of argument:
# keyword argument
# positional argument

# Python >> 3.4.2 Documentation >> The Python Tutorial >>
# 4.6. Defining Functions
# This tutorial introduces two new glossaries:
# mandatory argument
# optional argument

# So, What is the meaning of these five glossary? There difference?
# mandatory argument
# optional argument
# keyword argument
# keyword only argument
# positional argument
# http://stackoverflow.com/questions/1419046/python-normal-arguments-vs-keyword-arguments
# http://stackoverflow.com/questions/13687043/python-optional-positional-and-keyword-arguments
# PEP 3102: https://www.python.org/dev/peps/pep-3102/

# More information about: Packing and Unpacking Arguments in Python
# http://hangar.runway7.net/python/packing-unpacking-arguments

# Python >> 3.4.2 Documentation >> Python Frequently Asked Questions
# How can I pass optional or keyword parameters from one function to another?
# From this FAQ, we know that:
# With the ** specifier in the function's parameter list, all keyword arguments
# are packed into a dict object. And we can pass the keyword arguments to another
# function with **.
# This technique is particularly useful when you want to define a decorator.
def complex_2(**kwargs):
    assert isinstance(kwargs, dict)
    return complex(**kwargs)

def test_kwargs():
    # Two ways to pass through keyword arguments
    # 1. Pass keyword arguments with each one preceded by an identifier
    print(complex_2(real = 3, imag = 5))
    # 2. Pass keyword arguments with a dictionary preceded by ** specifier/operator
    #    This technique is also called "Unpacking Arguments Lists"
    print(complex_2(**{'real': 3, 'imag': 5}))

def test_args():
    # With the * operator, all positional arguments are packed in to a tuple.
    func = lambda *args: print(args)
    
    # There are also two ways to pass through positional arguments to a function
    # 1. Pass them one by one at the beginning of an argument list
    func(1, 2, 3, 4)
    # 2. Pass them as the elements of an iterable object proceded by * specifier/operator
    #    This technique is also called 'Unpacking Argument Lists' in this page:
    #    Python >> 3.4.2 Documentation >> The Python Tutorial / 4.7.4. Unpacking Argument Lists
    func(*(1, 2, 3, 4))
    func(*(i for i in range(1, 5)))
    func(*[1, 2, 3, 4])
    # here, we only pass a tuple to the function
    func((1, 2, 3, 4))

if __name__ == '__main__':
    test_kwargs()
    test_args()

