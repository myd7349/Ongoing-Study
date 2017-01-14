#! /usr/bin/env python3
# coding: utf-8

# 2017-01-14T19:25:30+08:00

import os
import os.path
import shutil

import cppimportex


full_path = lambda f: os.path.join(os.path.dirname(__file__), f)


if __name__ == '__main__':    
    for i in range(3):
        module_name = 'iota_{0}'.format(i)
        cpp_path = full_path(module_name+'.cpp')

        shutil.copy(full_path('iota.cpp'), cpp_path)
        m = cppimportex.imp(module_name, end=i, module_name=module_name)
        print(m.iota())
        os.remove(cpp_path)
