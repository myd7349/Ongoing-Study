#! /usr/bin/env python3
# -*- coding: utf-8 -*-

num = 0x0201

try:
    num_bytes = bytes([num])
    print(num_bytes)
except Exception as e:
    print(e)

import struct

print(struct.pack('I', num))
print("Little endian:", struct.pack('<I', num))
print("Big endian:", struct.pack('>I', num))


# References:
# [Converting int to bytes in Python 3](https://stackoverflow.com/questions/21017698/converting-int-to-bytes-in-python-3)
# [How to convert integer value to array of four bytes in python](https://stackoverflow.com/questions/6187699/how-to-convert-integer-value-to-array-of-four-bytes-in-python)
# Ongoing-Study/algorithm/os/HostByteOrder
