#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-03-23T11:26+08:00

__version__ = 'v0.1.0'

import os.path

import rescrawler


class Tanenbaum5eVideoNotesCrawler(rescrawler.ResourceCrawler):
    def __init__(self, prog, ver):
        super().__init__(prog, ver)
    
    def get_description(self):
        return 'Tanenbaum, Wetherall Computer Networks 5e video notes downloader.'
    
    def get_url(self):
        return 'http://media.pearsoncmg.com/ph/streaming/esm/tanenbaum5e_videonotes/tanenbaum_videoNotes.html'
    
    def get_re(self):
        return r'.+\.m4v'


def main():
    prog = os.path.basename(__file__)
    Tanenbaum5eVideoNotesCrawler(prog, __version__).run()

    
if __name__ == '__main__':
    main()
