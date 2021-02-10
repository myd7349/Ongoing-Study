#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# $ yapf -i math_eval.py

import ast
import importlib.util
import operator
import os.path

base_dir = os.path.dirname(__file__)
module_path = os.path.join(base_dir, 'pyparsing', 'math_eval.py')

math_eval_impl_spec = importlib.util.spec_from_file_location(
    'math_eval_impl', module_path)
math_eval_impl = importlib.util.module_from_spec(math_eval_impl_spec)
math_eval_impl_spec.loader.exec_module(math_eval_impl)

math_eval_ex = math_eval_impl.math_eval

# Supported operators
operators = {
    ast.Add: operator.add,
    ast.Sub: operator.sub,
    ast.Mult: operator.mul,
    ast.Div: operator.truediv,
    ast.Pow: operator.pow,
    ast.BitXor: operator.xor,
    ast.USub: operator.neg
}


def eval_(node):
    if isinstance(node, ast.Num):  # <number>
        return node.n
    elif isinstance(node, ast.BinOp):  # <left> <operator> <right>
        return operators[type(node.op)](eval_(node.left), eval_(node.right))
    elif isinstance(node, ast.UnaryOp):  # <operator> <operand> e.g., -1
        return operators[type(node.op)](eval_(node.operand))
    else:
        raise TypeError(node)


def math_eval(expr):
    """
    >>> eval_expr('2^6')
    4
    >>> eval_expr('2**6')
    64
    >>> eval_expr('1 + 2*3**(4^5) / (6 + -7)')
    -5.0
    """
    return eval_(ast.parse(expr, mode='eval').body)


def main():
    exprs = ('0.001', '1.0 / 1000', '2 ^ 10')

    for expr in exprs:
        print(math_eval(expr), math_eval_ex(expr))


if __name__ == '__main__':
    main()

# References:
# [Import Local module over global python](https://stackoverflow.com/questions/11489330/import-local-module-over-global-python)
# [How to import a module given the full path?](https://stackoverflow.com/questions/67631/how-to-import-a-module-given-the-full-path)
# [Evaluating a mathematical expression in a string](https://stackoverflow.com/questions/2371436/evaluating-a-mathematical-expression-in-a-string)
# [Python eval(): Evaluate Expressions Dynamically](https://realpython.com/python-eval-function/)
# [Python: make eval safe](https://stackoverflow.com/questions/3513292/python-make-eval-safe)
