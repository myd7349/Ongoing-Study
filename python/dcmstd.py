#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-04-16T18:03+08:00

__version__ = 'v0.1.0'

import os.path

import rescrawler


class DICOMStandardCrawler(rescrawler.ResourceCrawler):
    def __init__(self, prog, ver):
        super().__init__(prog, ver)
    
    def get_description(self):
        return 'DICOM Standard documentations downloader.'
    
    def get_url(self):
        return 'https://www.dicomstandard.org/current/'
    
    def get_re(self):
        return r'.+/part[0-9]{2}\.(pdf|html|docx|odt)'


def main():
    prog = os.path.basename(__file__)
    DICOMStandardCrawler(prog, __version__).run()

    
if __name__ == '__main__':
    main()
