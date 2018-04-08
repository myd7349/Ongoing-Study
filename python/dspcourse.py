#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-04-08T09:15+08:00

__version__ = 'v0.1.0'

import os.path

import rescrawler


class DSPCourseSlidesCrawler(rescrawler.ResourceCrawler):
    def __init__(self, prog, ver):
        super().__init__(prog, ver)
    
    def get_description(self):
        return 'DSP Course slides downloader.'
    
    def get_url(self):
        return 'http://www.cmlab.csie.ntu.edu.tw/DSPCourse/slide/'
    
    def get_re(self):
        return r'.+\.(pdf|ppt)'


def main():
    prog = os.path.basename(__file__)
    DSPCourseSlidesCrawler(prog, __version__).run()

    
if __name__ == '__main__':
    main()
