#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import binascii


# This is what you saw in a hex viewer.
references = '''
68 74 74 70 73 3A 2F 2F 73 74 61 63 6B 6F 76 65
72 66 6C 6F 77 2E 63 6F 6D 2F 71 75 65 73 74 69
6F 6E 73 2F 31 34 32 35 34 39 33 2F 63 6F 6E 76
65 72 74 2D 68 65 78 2D 74 6F 2D 62 69 6E 61 72
79 0D 0A 68 74 74 70 73 3A 2F 2F 63 6F 64 65 72
65 76 69 65 77 2E 73 74 61 63 6B 65 78 63 68 61
6E 67 65 2E 63 6F 6D 2F 71 75 65 73 74 69 6F 6E
73 2F 31 34 37 32 32 35 2F 70 79 74 68 6F 6E 2D
68 65 78 2D 76 69 65 77 65 72 0D 0A
'''

table = {
    '\t': None,
    ' ': None,
    '\r': None,
    '\n': None,
}

urls = references.translate(str.maketrans(table))
print(urls)

urls = binascii.unhexlify(urls).decode('ascii')
print(urls)
