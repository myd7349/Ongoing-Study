#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-01-19T16:50+08:00

__version__ = 'v0.1.0'

import os.path

import rescrawler


class Algs4LecturesCrawler(rescrawler.ResourceCrawler):
    def __init__(self, prog, ver):
        super().__init__(prog, ver)
    
    def get_description(self):
        return 'Algorithms 4th Edition Lectures Downloader.'
    
    def get_url(self):
        return 'https://algs4.cs.princeton.edu/lectures/'
    
    def get_re(self):
        return r'.+((pdf)|(mov))' 


def main():
    prog = os.path.basename(__file__)
    Algs4LecturesCrawler(prog, __version__).run()

    
if __name__ == '__main__':
    main()
