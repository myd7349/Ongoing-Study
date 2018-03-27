#! /usr/bin/env python3
# -*- coding: utf-8 -*- 
# 2014-01-11T18:37+08:00

# http://blog.csdn.net/ubiter/article/details/18408273

# 2015-04-19T11:20+08:00

import re


def parse_re(str_re = ''):
    from os import name as os_name
    from subprocess import check_output
    
    args = ['python' if os_name == 'nt' else 'python3', '-c',
            'import re; re.compile(r"{0}", re.DEBUG)'.format(str_re)]
    # Potential exception: subprocess.CalledProcessError
    parse_ret = check_output(args, universal_newlines = True)

    ######################################################################
    literal_group = 'LITERAL'
    # The RE below is not so good since we will lost string 'literal' in the parse result.
    # literal_re = r'[\t ]*literal[\t ]+(?P<{0}>[0-9]+)'.format(literal_group)
    # However, positive look-behind assertion requires fixed-width pattern. So RE below isn't right.
    # literal_re = r'(?<=[\t ]*literal[\t ]+)(?P<{0}>[0-9]+)'.format(literal_group)
    # This one is simple but enough for use.
    literal_re = r'(?<=literal )(?P<{0}>[0-9]+)'.format(literal_group)
    literal_pat = re.compile(literal_re, re.IGNORECASE)
    
    repl_callback = lambda match_ret: \
                    chr(int(match_ret.group(literal_group))) + \
                    ' ({0:#x})'.format(int(match_ret.group(literal_group)))

    if literal_pat.search(parse_ret):
        parse_ret = literal_pat.sub(repl_callback, parse_ret)

    ######################################################################
    range_down_group = 'RANGE_DOWN'
    range_up_group = 'RANGE_UP'
    range_re = r'(?<=range )\((?P<{0}>[0-9]+), (?P<{1}>[0-9]+)\)' \
               .format(range_down_group, range_up_group)
    range_pat = re.compile(range_re, re.IGNORECASE)

    def range_repl_callback(match_ret):
        down = int(match_ret.group(range_down_group))
        up = int(match_ret.group(range_up_group))
        return '({0}, {1}) ({2:#x}, {3:#x})' \
               .format(chr(down), chr(up), down, up)

    if range_pat.search(parse_ret):
        parse_ret = range_pat.sub(range_repl_callback, parse_ret)
         
    return parse_ret

if __name__ == '__main__':
    from sys import argv
    
    if len(argv) >= 2:
        print(parse_re(argv[1]), end = '')
    else:
        print(parse_re(r'([[:alpha:]][[:alnum:]_]*) = \1'), end = '')
        print(parse_re(r'[A-Za-z][0-9]'), end = '')
