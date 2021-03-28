#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# $ yapf -i math_eval_v0.py

import ast
import operator

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
        print(math_eval(expr))


if __name__ == '__main__':
    main()

# Output:
# 0.001
# 0.001
# 8

# References:
# [Evaluating a mathematical expression in a string](https://stackoverflow.com/questions/2371436/evaluating-a-mathematical-expression-in-a-string)
# [Python eval(): Evaluate Expressions Dynamically](https://realpython.com/python-eval-function/)
# [Python: make eval safe](https://stackoverflow.com/questions/3513292/python-make-eval-safe)
# https://github.com/kimwalisch/calculator
