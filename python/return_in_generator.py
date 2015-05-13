#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-05-12T16:40+08:00

def main():
    import array
    import struct

    #---------------------------------------------------------------------------
    # Suppose that we got a C-style integer array that contains 10 integers:
    #   int data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    # then how is this array stored in memory?
    
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

    #---------------------------------------------------------------------------
    # unpack_data_v0 itself is a function that returns an iterable object.
    # unpack_data_v1 itself is a generator function.
    # Besides, there is no difference between them.
    def unpack_data_v0():
        return struct.iter_unpack('=i', data)
    def unpack_data_v1():
        yield from struct.iter_unpack('=i', data)

    for i in unpack_data_v0():
        print(*i, end = ' ')
    print()
    
    for i in unpack_data_v1():
        print(*i, end = ' ')
    print()

    #---------------------------------------------------------------------------
    # However, it is not always the case. For example, in a generator function
    # we can only use `yield from`, not `return`.
    def unpack_data_v3(do_real_work = True):
        if do_real_work:
            return struct.iter_unpack('=i', data)
        else:
            for i in (1, 1, 2, 3, 5, 8, 13, 21):
                yield i,

    def unpack_data_v4(do_real_work = True):
        if do_real_work:
            yield from struct.iter_unpack('=i', data)
        else:
            for i in (1, 1, 2, 3, 5, 8, 13, 21):
                yield i,      

    for i in unpack_data_v3():
        print(*i, end = ' ')
    print()
    
    for i in unpack_data_v4():
        print(*i, end = ' ')
    print()

    for i in unpack_data_v3(False):
        print(*i, end = ' ')
    print()
    
    for i in unpack_data_v4(False):
        print(*i, end = ' ')
    print()
    
if __name__ == '__main__':
    main()

# References:
# [Python 3.4.3 documentation/The Python Standard Library/4.8. Binary Sequence Types — bytes, bytearray, memoryview]
# [Python 3.4.3 documentation/The Python Language Reference/6.2.9.1. Generator-iterator methods]
# [PEP 0380 -- Syntax for Delegating to a Subgenerator](https://www.python.org/dev/peps/pep-0380/)
# [Python: generator expression vs. yield](http://stackoverflow.com/questions/1995418/python-generator-expression-vs-yield)
# [Return in generator together with yield in Python 3.3](http://stackoverflow.com/questions/16780002/return-in-generator-together-with-yield-in-python-3-3)
# [What does the yield keyword do in Python?](http://stackoverflow.com/questions/231767/what-does-the-yield-keyword-do-in-python)
# [python中的协程（yield）内部是怎么实现的？](http://www.zhihu.com/question/30133749/)
