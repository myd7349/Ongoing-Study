#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 2014-10-11T14:59+08:00

# This program is inspired by an example in "Dive into Python3" and some code
# is based on a python script named "roman.py" available at: 
# http://www.diveintopython.net/unit_testing/stage_4.html
# and an extended javascript implementation available at:
# http://jeankorte.ca/jk-roman-numeral-converter.html

'''Converting Roman Numerals to Arabic Numbers and vice versa.'''

import re

class RomanError(ValueError): pass
class InvalidRomanNumeral(RomanError): pass
class InvalidInteger(RomanError): pass
class OutOfRange(RomanError): pass

roman_arabic_map = (
    # In extended mode, arabic numbers in range [1, 3999999] can be converted,
    # and the longest roman numeral is mmmdccclxxxvMMMDCCCLXXXVIII(3888888).
    ('m', 1000000),
    ('cm', 900000),
    ('d', 500000),
    ('cd', 400000),
    ('c', 100000),
    ('xc', 90000),
    ('l', 50000),
    ('xl', 40000),
    ('x', 10000),
    ('Mx', 9000),
    ('v', 5000),
    ('Mv', 4000),
    #('i', 1000),
    # -------------------------------------------------------------------------
    # In traditional mode, roman numerals in range [1, 3999] can be converted,
    # and the longest roman numeral is MMMDCCCLXXXVIII(3888).
    ('M', 1000),
    ('CM', 900),
    ('D', 500),
    ('CD', 400),
    ('C', 100),
    ('XC', 90),
    ('L', 50),
    ('XL', 40),
    ('X', 10),
    ('IX', 9),
    ('V', 5),
    ('IV', 4),
    ('I', 1))

def str_to_int(integer):
    '''Convert a string to an integer.

    >>> str_to_int('12')
    12
    >>> str_to_int('0x12')
    18
    >>> str_to_int('012')
    10
    >>> str_to_int('012a')
    Traceback (most recent call last):
        ...
    ValueError: invalid literal for int() with base 8: '012a'
    >>> str_to_int(None)
    Traceback (most recent call last):
        ...
    InvalidInteger: a "str" object is excepted
    '''
    if isinstance(integer, str):
        integer = integer.strip()
        if integer.startswith('0x'):
            base = 16
        elif integer.startswith('0'):
            base = 8
        else:
            base = 10

        return int(integer, base)

    raise InvalidInteger('a "str" object is excepted')

def from_roman(roman, exmode = False):
    '''Convert a roman numeral to an integer.

    TODO: Complete doctest based on the test cases on
    http://ostermiller.org/calc/roman.html
    '''
    if not isinstance(roman, str):
        raise InvalidRomanNumeral('A valid roman numeral must be a "str" object')

    roman = roman.strip().replace('i', 'M')
    if not is_roman(roman, exmode):
        raise InvalidRomanNumeral('Invalid roman numeral')

    assert len(roman_arabic_map) > 12 and roman_arabic_map[12][0] == 'M'

    arabic = 0
    index = 0
    roman_len = len(roman)
    for i in range(0 if exmode else 12, len(roman_arabic_map)):
        pat_len = len(roman_arabic_map[i][0])
        while index + pat_len <= roman_len and \
              roman[index:index+pat_len] == roman_arabic_map[i][0]:
            arabic += roman_arabic_map[i][1]
            index += pat_len
        if index == roman_len:
            break

    return arabic

def to_roman(arabic, exmode = False):
    '''Convert an integer to a roman numeral.

    TODO: Complete doctest based on the test cases on
    http://ostermiller.org/calc/roman.html'''
    if isinstance(arabic, str):
        arabic = str_to_int(arabic)

    largest = 3999999 if exmode else 3999
    if not 1 <= arabic <= largest:
        raise OutOfRange('Number not in range: [1, {}]'.format(largest))

    assert len(roman_arabic_map) > 12 and roman_arabic_map[12][0] == 'M'
    
    roman = ''
    for i in range(0 if exmode else 12, len(roman_arabic_map)):
        while arabic >= roman_arabic_map[i][1]:
            roman += roman_arabic_map[i][0]
            arabic -= roman_arabic_map[i][1]
        if arabic == 0:
            break

    return roman

def is_roman(roman, exmode = False):
    'Validate a roman numeral.'
    if not isinstance(roman, str):
        return False

    roman = roman.strip().replace('i', 'M')
    if len(roman) == 0:
        return False
    
    roman_pat = re.compile('^' + (
        """
        m{0,3}           # millions - 0 to 3 m's
        (cm|cd|d?c{0,3}) # hundred thousands
        (xc|xl|l?x{0,3}) # ten thousands
        (Mx|Mv|v?M{0,3}) # thousands
        """ if exmode else \
        """
        M{0,3}           # thousands - 0 to 3 M's
        """) + \
        """
        (CM|CD|D?C{0,3}) # hundreds - 900 (CM), 400 (CD),
                         #            0-300 (0 to 3 C's) or 
                         #            500-800 (D, followed by 0 to 3 C's)
        (XC|XL|L?X{0,3}) # tens - 90 (XC), 40 (XL), 0-30(0 to 3 X's)
                         #        or 50-80 (L, followed by 0 to 3 X's)
        (IX|IV|V?I{0,3}) # ones - 9 (IX), 4(IV), 0-3 (0 to 3 I's)
                         #        or 5-8 (V, followed by 0 to 3 I's)
        $""", re.VERBOSE)
    
    return bool(roman_pat.match(roman))

def do_test():
    while True:
        #print(to_roman(input(), True))
        print(from_roman(input(), True))
        
if __name__ == '__main__':
    import doctest
    doctest.testmod()

    # TODO: provide a GUI here

