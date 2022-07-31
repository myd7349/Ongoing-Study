#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import argparse
import io
import os.path
import sys

import parse


def extract_coefficients(file, prefix, indent):
    assign_count = 0

    rows_of_num = 0
    rows_of_den = 0

    num_def = io.StringIO()
    den_def = io.StringIO()
    gain_def = io.StringIO()

    if prefix is None:
        prefix = ''

    print(
        f'public static readonly double[,] {prefix}Numerator = new double[,]\n{{',
        file=num_def)
    print(
        f'public static readonly double[,] {prefix}Denominator = new double[,]\n{{',
        file=den_def)
    print(f'public static readonly double[] {prefix}Gain = new double[]\n{{',
          file=gain_def)

    #with open(file, 'rb') as fp:
    #    for line in fp:
    #        print(parse.parse(b'{}, {}, {}', line))

    with open(file, 'r') as fp:
        for line in fp:
            #print(parse.parse('{:f}, {:f}, {:f}', line)) # Not work. Why???
            result = parse.parse('{}, {}, {}', line)
            if not result:
                if ' = ' in line:
                    assign_count += 1
                continue

            assert assign_count in (2, 4)

            nums = tuple((num.rstrip() for num in result.fixed))
            num1, num2, num3 = (num.lstrip() for num in nums)

            if assign_count == 2:
                rows_of_num += 1

                if rows_of_num % 2 != 0:
                    assert num2 == '0'
                    assert num3 == '0'

                    if num1 != '1':
                        gain_def.write(f'    {num1},\n')
                else:
                    assert num1 == '1'

                    num_def.write(
                        f'    {{{nums[0]}, {nums[1]}, {nums[2]} }},\n')
            else:
                rows_of_den += 1

                if rows_of_den % 2 != 0:
                    assert num1 == '1'
                    assert num2 == '0'
                    assert num3 == '0'
                else:
                    assert num1 == '1'

                    den_def.write(
                        f'    {{{nums[0]}, {nums[1]}, {nums[2]} }},\n')

    print('};', file=num_def)
    print('};', file=den_def)
    print('};', file=gain_def)

    if not indent:
        print(num_def.getvalue())
        print(den_def.getvalue())
        print(gain_def.getvalue())
    else:
        indent_str = indent * ' '

        num_def.seek(0)
        for line in num_def:
            print(f'{indent_str}{line}', end='')

        den_def.seek(0)
        for line in den_def:
            print(f'{indent_str}{line}', end='')

        gain_def.seek(0)
        for line in gain_def:
            print(f'{indent_str}{line}', end='')


def main():
    prog = os.path.splitext(os.path.basename(sys.argv[0]))[0]

    parser = argparse.ArgumentParser(
        prog=prog,
        description='Extract coefficients from C header files.',
    )

    parser.add_argument('-f', '--file', required=True, help='Input file path')
    parser.add_argument('--encoding', help='Input file encoding')
    parser.add_argument('--prefix', help='Variable name prefix')
    parser.add_argument('-i', '--indent', type=int, default=0, help='Indent')

    args = parser.parse_args()

    if not os.path.isfile(args.file):
        sys.stderr.write('Input file \'{0}\' doesn\'t exist!\n'.format(
            args.input_file))
        sys.exit(1)

    if args.indent < 0:
        sys.stderr.write('Indent should be a positive integer.\n')
        sys.exit(2)

    extract_coefficients(args.file, args.prefix, args.indent)


if __name__ == '__main__':
    main()


# References:
# [How do I escape curly-brace ({}) characters in a string while using .format (or an f-string)?](https://stackoverflow.com/questions/5466451/how-do-i-escape-curly-brace-characters-in-a-string-while-using-format-or)
