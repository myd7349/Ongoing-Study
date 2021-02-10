#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# $ yapf -i math_eval.py

import ast
import importlib.util
import operator
import os.path

base_dir = os.path.dirname(__file__)
module_path = os.path.join(base_dir, '../', 'math_eval_v1.py')

math_eval_impl_spec = importlib.util.spec_from_file_location(
    'math_eval_impl', module_path)
math_eval_impl = importlib.util.module_from_spec(math_eval_impl_spec)
math_eval_impl_spec.loader.exec_module(math_eval_impl)

math_eval = math_eval_impl.math_eval


def main():
    exprs = ('0.001', '1.0 / 1000', '2 ^ 10')

    for expr in exprs:
        print(math_eval(expr))


if __name__ == '__main__':
    main()

# Output:
# 0.001
# 0.001
# 1024

# References:
# [Import Local module over global python](https://stackoverflow.com/questions/11489330/import-local-module-over-global-python)
# [How to import a module given the full path?](https://stackoverflow.com/questions/67631/how-to-import-a-module-given-the-full-path)
# [Evaluating a mathematical expression in a string](https://stackoverflow.com/questions/2371436/evaluating-a-mathematical-expression-in-a-string)
# [Python eval(): Evaluate Expressions Dynamically](https://realpython.com/python-eval-function/)
# [Python: make eval safe](https://stackoverflow.com/questions/3513292/python-make-eval-safe)
