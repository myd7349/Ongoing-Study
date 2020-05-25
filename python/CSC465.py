#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-08-03T18:27+08:00

__version__ = 'v0.1.0'

import os.path

import rescrawler


class CSC465Crawler(rescrawler.ResourceCrawler):
    def __init__(self, prog, ver):
        super().__init__(prog, ver)
    
    def get_description(self):
        return 'CSC465 Resources Downloader.'
    
    def get_url(self):
        return 'http://web.cs.unlv.edu/jh/CSC465/'
    
    def get_re(self):
        return r'.+((htm)|(html)|(pdf)|(h))' 


def main():
    prog = os.path.basename(__file__)
    CSC465Crawler(prog, __version__).run()

    
if __name__ == '__main__':
    main()
