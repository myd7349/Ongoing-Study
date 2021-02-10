#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# $ yapf -i math_eval.py

# https://github.com/pyparsing/pyparsing/blob/master/examples/fourFn.py
# fourFn.py
#
# Demonstration of the pyparsing module, implementing a simple 4-function expression parser,
# with support for scientific notation, and symbols for e and pi.
# Extended to add exponentiation and simple built-in functions.
# Extended test cases, simplified pushFirst method.
# Removed unnecessary expr.suppress() call (thanks Nathaniel Peterson!), and added Group
# Changed fnumber to use a Regex, which is now the preferred method
# Reformatted to latest pypyparsing features, support multiple and variable args to functions
#
# Copyright 2003-2019 by Paul McGuire
#

import math
import operator
import sys

import pyparsing

# map operator symbols to corresponding arithmetic operations
EPSILON = sys.float_info.epsilon

operators = {
    "+": operator.add,
    "-": operator.sub,
    "*": operator.mul,
    "/": operator.truediv,
    "^": operator.pow,
}

functions = {
    "sin": math.sin,
    "cos": math.cos,
    "tan": math.tan,
    "exp": math.exp,
    "abs": abs,
    "trunc": int,
    "round": round,
    "sgn": lambda a: -1 if a < -EPSILON else 1 if a > EPSILON else 0,
    # functionsl with multiple arguments
    "multiply": lambda a, b: a * b,
    "hypot": math.hypot,
    # functions with a variable number of arguments
    "all": lambda *a: all(a),
}


def aton(s):
    try:
        return int(s)
    except:
        return float(s)


def evaluate_stack(s, **kwargs):
    op, num_args = s.pop(), 0
    if isinstance(op, tuple):
        op, num_args = op
    if op == "unary -":
        return -evaluate_stack(s, **kwargs)
    if op in "+-*/^":
        # note: operands are pushed onto the stack in reverse order
        op2 = evaluate_stack(s, **kwargs)
        op1 = evaluate_stack(s, **kwargs)
        return operators[op](op1, op2)
    elif op == "PI":
        return math.pi  # 3.1415926535
    elif op == "E":
        return math.e  # 2.718281828
    elif op in functions:
        # note: args are pushed onto the stack in reverse order
        args = reversed([evaluate_stack(s, **kwargs) for _ in range(num_args)])
        return functions[op](*args)
    elif op[0].isalpha():
        if op in kwargs:
            return aton(kwargs[op])
        else:
            raise Exception("Invalid identifier '{0}'".format(op))
    else:
        # try to evaluate as int first, then as float if int fails
        return aton(op)


class BNF:
    """
    expop   :: '^'
    multop  :: '*' | '/'
    addop   :: '+' | '-'
    integer :: ['+' | '-'] '0'..'9'+
    atom    :: PI | E | real | fn '(' expr ')' | '(' expr ')'
    factor  :: atom [ expop factor ]*
    term    :: factor [ multop factor ]*
    expr    :: term [ addop term ]*
    """
    def __init__(self):
        self._expr_stack = []

        # use CaselessKeyword for e and pi, to avoid accidentally matching
        # functions that start with 'e' or 'pi' (such as 'exp'); Keyword
        # and CaselessKeyword only match whole words
        e = pyparsing.CaselessKeyword("E")
        pi = pyparsing.CaselessKeyword("PI")

        # fnumber = Combine(Word("+-"+nums, nums) +
        #                    Optional("." + Optional(Word(nums))) +
        #                    Optional(e + Word("+-"+nums, nums)))
        # or use provided pyparsing_common.number, but convert back to str:
        # fnumber = ppc.number().addParseAction(lambda t: str(t[0]))
        fnumber = pyparsing.Regex(r"[+-]?\d+(?:\.\d*)?(?:[eE][+-]?\d+)?")
        ident = pyparsing.Word(pyparsing.alphas, pyparsing.alphanums + "_$")

        plus, minus, mult, div = map(pyparsing.Literal, "+-*/")
        lpar, rpar = map(pyparsing.Suppress, "()")
        addop = plus | minus
        multop = mult | div
        expop = pyparsing.Literal("^")

        expr = pyparsing.Forward()
        expr_list = pyparsing.delimitedList(pyparsing.Group(expr))

        # add parse action that replaces the function identifier with a (name, number of args) tuple
        def insert_fn_argcount_tuple(t):
            fn = t.pop(0)
            num_args = len(t[0])
            t.insert(0, (fn, num_args))

        fn_call = (ident + lpar - pyparsing.Group(expr_list) +
                   rpar).setParseAction(insert_fn_argcount_tuple)
        atom = (addop[...] +
                ((fn_call | pi | e | fnumber | ident).setParseAction(
                    self._push_front)
                 | pyparsing.Group(lpar + expr + rpar))).setParseAction(
                     self._push_unary_minus)

        # by defining exponentiation as "atom [ ^ factor ]..." instead of "atom [ ^ atom ]...", we get right-to-left
        # exponents, instead of left-to-right that is, 2^3^2 = 2^(3^2), not (2^3)^2.
        factor = pyparsing.Forward()
        factor <<= atom + (expop + factor).setParseAction(
            self._push_front)[...]
        term = factor + (multop + factor).setParseAction(self._push_front)[...]
        expr <<= term + (addop + term).setParseAction(self._push_front)[...]

        self._bnf = expr

    def math_eval(self, expr, **kwargs):
        self._parse_string(expr)
        return evaluate_stack(self._expr_stack[:], **kwargs)

    def _push_front(self, toks):
        self._expr_stack.append(toks[0])

    def _push_unary_minus(self, toks):
        for t in toks:
            if t == "-":
                self._expr_stack.append("unary -")
            else:
                break

    def _parse_string(self, expr, parse_all=True):
        self._expr_stack = []
        return self._bnf.parseString(expr, parseAll=parse_all)


_bnf = None


def math_eval(expr, **kwargs):
    global _bnf
    if not _bnf:
        _bnf = BNF()
    return _bnf.math_eval(expr, **kwargs)


def main():
    for i in range(100 + 1):
        print(math_eval('x^2', x=i))


if __name__ == '__main__':
    main()

# References:
# [Evaluating a mathematical expression in a string](https://stackoverflow.com/questions/2371436/evaluating-a-mathematical-expression-in-a-string)
# [Python eval(): Evaluate Expressions Dynamically](https://realpython.com/python-eval-function/)
# [Python: make eval safe](https://stackoverflow.com/questions/3513292/python-make-eval-safe)
# [Parse mathematical expressions with pyparsing](https://stackoverflow.com/questions/23879784/parse-mathematical-expressions-with-pyparsing)
# [Value for epsilon in Python](https://stackoverflow.com/questions/9528421/value-for-epsilon-in-python)
