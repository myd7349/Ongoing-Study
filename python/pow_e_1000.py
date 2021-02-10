#!/usr/bin/env python3
# coding: utf-8

print(2 ** 1000)
print(3 ** 1000) # OK

e = 2.71828

try:
    print(e ** 1000) # Overflow
except OverflowError as ex:
    print(ex)
