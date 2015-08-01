#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-07-11T13:03+08:00

class UnsafeError(Exception): pass


def safe_eval(expr, allow_doublescore=False):
    """A relatively safe `eval`."""
    if not allow_doublescore and '__' in expr:
        raise UnsafeError('For security propose, double underscore is not allowed')

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
