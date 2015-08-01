#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-08-02T00:26+08:00

import io
import tokenize

# How to tokenize a str object?


def tokenize_str(s):
    # The Python documentation shows us this method.
    return tokenize.tokenize(io.BytesIO(s.encode('utf-8')).readline)


def tokenize_str_2(s):
    #def helper():
    #    yield s
    #return tokenize.generate_tokens(helper().__next__)

    # Note that, `generate_tokens` is an undocumented API.
    return tokenize.generate_tokens(iter((s, )).__next__)


if __name__ == '__main__':
    code = 'print("Hello, world!")'

    for tok in tokenize_str(code):
        print(tok)
    print(79 * '-')
    for tok in tokenize_str_2(code):
        print(tok)    
    
    
