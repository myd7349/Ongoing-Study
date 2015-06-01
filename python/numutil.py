#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-03-27T10:30+08:00
    
def aton(num):
    '''Convert string to number.
    The return value may be an integer or a floating point number.

    >>> aton('12')
    12
    >>> aton('0x12')
    18
    >>> aton('012')
    10
    >>> aton('0o12 ')
    10
    >>> print('{:.2f}'.format(aton('3.14159')))
    3.14
    >>> aton('012a')
    Traceback (most recent call last):
        ...
    ValueError: invalid literal for int() with base 8: '012a'
    >>> aton(None)
    Traceback (most recent call last):
        ...
    TypeError: Invalid "str" object
    >>> aton(10)
    Traceback (most recent call last):
        ...
    TypeError: Invalid "str" object
    >>> aton(3.14)
    Traceback (most recent call last):
        ...
    TypeError: Invalid "str" object
    '''
    if not isinstance(num, str):
        raise TypeError('Invalid "str" object')

    if '.' in num:
        return float(num)
    else:
        try:
            # In Python 3.x, octal string literals starts with '0o', not '0', so
            # a Python 2.6 style octal string literals('077', for instance) will
            # cause a ValueError here.
            return int(num, 0)
        except ValueError:
            # Make it possible to handle Python 2.6 style octal string literals.
            if num.startswith('0'):
                return int(num, 8)
            raise

def atof(num):
    '''Convert string to floating point number.

    >>> format(atof('0xa'), '.1f')
    '10.0'
    '''
    return float(aton(num))

def atoi(num):
    '''Convert string to integer.'''
    return int(aton(num))

def to_num(num):
    '''Convert anything to number.

    >>> to_num(123)
    123
    >>> print('{:.2f}'.format(to_num(3.1415926)))
    3.14
    '''
    if isinstance(num, (int, float)):
        return num
    else:
        return aton(num)

def to_float(num):
    '''Convert anything to float.'''
    return float(to_num(num))
    
def to_int(num):
    '''Convert anything to integer.

    >>> to_int(3.14)
    3
    >>> to_int(' 3.14 ')
    3
    '''
    return int(to_num(num))

if __name__ == '__main__':
    import doctest
    doctest.testmod()
    
# References:
# [Convert a string to integer with decimal in Python](http://stackoverflow.com/questions/1094717/convert-a-string-to-integer-with-decimal-in-python)
# [Convert hex string to int in Python](http://stackoverflow.com/questions/209513/convert-hex-string-to-int-in-python)
# [Invalid Token when using Octal numbers](http://stackoverflow.com/questions/1837874/invalid-token-when-using-octal-numbers)
# [Parse String to Float or Int](http://stackoverflow.com/questions/379906/parse-string-to-float-or-int)
