#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-01-16T10:12+08:00

__version__ = 'v0.1.0'

import os.path

import rescrawler


class MITBITDBCrawler(rescrawler.ResourceCrawler):
    def __init__(self, prog, ver):
        super().__init__(prog, ver)
    
    def get_description(self):
        return 'MIT-BIH Arrhythmia Database downloader.'
    
    def get_url(self):
        return 'https://physionet.org/physiobank/database/mitdb/'
    
    def get_re(self):
        return r'\d{3}\.((atr)|(dat)|(hea))' 


def main():
    prog = os.path.basename(__file__)
    MITBITDBCrawler(prog, __version__).run()
    
    
if __name__ == '__main__':
    main()
