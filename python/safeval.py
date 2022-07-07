#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-07-11T13:03+08:00

import tokenize


class UnsafeError(Exception): pass


# It's not easy to make `eval` safe and useful at the same time.
# When I say `useful` I mean that what I want is not another
# `ast.literal_eval`. Instead, I want `safe_eval`  be able to do more.
# For example, some builtin functions like `int`, 'float' are safe,
# so I shouldn't hide them all from `safe_eval`.
# eval(expr, {'__builtins__': {}}, {}), is safe, but useless.
# Here, I will define some rules to make the call to `eval` more safer:
#   1. Calling arbitrary functions without limitations is dangerous, so
#      a white list is defined. Only those functions that in this list
#      can be appeared in the input expression. This list, of course,
#      is immutable.
#      (Since, `copy.deepcopy` will never create a deep copy of a function
#       so things like this won't bother us:
#         allowed_list = (sin, cos)
#         import copy, os
#         sin = copy.deepcopy(os.system)
#      )
#   2. Only object of those builtin types are allowed in the expression.
#      (So that things like below won't happen:
#         class Foo:
#             def __init__(self):
#                 os.system('/bin/sh')
#         safe_eval('Foo()')
#      )
def safe_eval(expr):
    """A relatively safe `eval`."""

    return eval(expr, {'__builtins__': {}}, {})


if __name__ == '__main__':
    import builtins
    import os
    import unittest

    class SafeEvalTest(unittest.TestCase):
        def test_double_underscore(self):
            self.assertRaises(UnsafeError, safe_eval, '__builtins__')
            self.assertEqual(safe_eval('__builtins__', True), {})
            self.assertRaises(UnsafeError, safe_eval, '__import__("urllib.parse")')
            self.assertRaises(NameError, safe_eval, '__import__("urllib.parse")', True)

        def test_globals_locals(self):
            self.assertRaises(NameError, safe_eval, 'os.system')
            self.assertRaises(NameError, safe_eval, 'builtins')

    unittest.main()


# References:
# [Exploiting eval() function in Python](http://vipulchaskar.blogspot.jp/2012/10/exploiting-eval-function-in-python.html)
# [Using eval() safely in python](http://lybniz2.sourceforge.net/safeeval.html)
# [Eval really is dangerous](http://www.nedbatchelder.com/blog/201206/eval_really_is_dangerous.html)
# Exploiting sloppy use of eval in Python:
#   [Part 1](https://2013.picoctf.com//problems/pyeval/stage1.html)
#   [Part 2](https://2013.picoctf.com//problems/pyeval/stage2.html)
#   [Part 3](https://2013.picoctf.com//problems/pyeval/stage3.html)
#   [Part 4](https://2013.picoctf.com//problems/pyeval/stage4.html)
# [# PicoCTF 2k13 - Python Eval 3](http://hacktracking.blogspot.jp/2014/01/picoctf-2k13-python-eval-3.html)
# [Exploiting Python’s Eval](http://www.floyd.ch/?p=584)
# https://github.com/FXuZ/colock-server/blob/master/colock/security.py
# [Evaluating a mathematical expression in a string](https://stackoverflow.com/questions/2371436/evaluating-a-mathematical-expression-in-a-string)
# [Python: make eval safe](https://stackoverflow.com/questions/3513292/python-make-eval-safe)
# https://github.com/zopefoundation/RestrictedPython
