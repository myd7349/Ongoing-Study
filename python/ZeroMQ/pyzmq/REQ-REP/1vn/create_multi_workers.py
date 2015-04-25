#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 2014-12-24T15:51+08:00

from multiprocessing import Process

import os

def proc():
    os.system('py -3 rep.py')
    
if __name__ == '__main__':
    procs_cnt = int(input('How many workers do you want to start: '))
    for i in range(procs_cnt):
        Process(target = proc, name = 'rep-{:02d}'.format(i+1)).start()
        
