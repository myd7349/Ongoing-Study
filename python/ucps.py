#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2014-11-25T17:11+08:00

# http://www.zhihu.com/question/26772647

# 2015-06-03T09:03+08:00
# http://www.zhihu.com/question/26921730

def ucps_to_str(cps):
    '''Translate an unicode code point sequence LITERAL like this:
        r'\u6d77\u9614\u5929\u7a7a'
    into a str object.'''
    cp_list = cps.replace(r'\u', ' ').split()
    return ''.join(chr(int(cp, 16)) for cp in cp_list)

def str_to_ucps(s):
    '''Translate a str object into an unicode code point sequence LITERAL.'''
    return ''.join(hex(ord(c)).replace('0x', r'\u') for c in s)

if __name__ == '__main__':
    cps = str_to_ucps('海阔天空')
    print(cps)
    print(ucps_to_str(cps))
    print('{!r}'.format(cps))
    print(repr(cps))

