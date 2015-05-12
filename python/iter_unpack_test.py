#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-05-12T16:40+08:00

def main():
    import array
    import struct

    # Suppose that we got a C-style integer array that contains 10 integers:
    #   int data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    # so how is this array stored in memory?
    
    data_range = range(10)

    # 0. The wrong way.
    data = bytearray()
    data.extend(data_range)
    data = bytes(data)
    print(data)
    
    # 1. One way.
    data = b''.join(struct.pack('=i', i) for i in data_range)
    print(data)

    # 2. Another way.
    data = array.array('i')
    data.extend(data_range)
    data = bytes(data)
    print(data)

if __name__ == '__main__':
    main()

# References:
# [Python 3.4.3 documentation/The Python Standard Library/4.8. Binary Sequence Types — bytes, bytearray, memoryview]
