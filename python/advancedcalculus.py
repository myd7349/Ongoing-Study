#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-04-08T09:48+08:00

__version__ = 'v0.1.0'

import os.path

import rescrawler


class AdvancedCalculusLecturesCrawler(rescrawler.ResourceCrawler):
    def __init__(self, prog, ver):
        super().__init__(prog, ver)
    
    def get_description(self):
        return 'Advanced Calculus lecture notes downloader.'
    
    def get_url(self):
        return 'https://ocw.mit.edu/courses/mathematics/18-075-advanced-calculus-for-engineers-fall-2004/lecture-notes/'
    
    def get_re(self):
        return r'.+\.pdf'


def main():
    prog = os.path.basename(__file__)
    AdvancedCalculusLecturesCrawler(prog, __version__).run()

    
if __name__ == '__main__':
    main()
