#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-03-23T11:26+08:00

__version__ = 'v0.1.0'

import os.path
import re

import pyquery

import rescrawler
import uriutils


class Tanenbaum5eVideoNotesCrawler(rescrawler.ResourceCrawler):
    def __init__(self, prog, ver):
        super().__init__(prog, ver)
    
    def get_description(self):
        return 'Tanenbaum, Wetherall Computer Networks 5e video notes downloader.'
    
    def get_url(self):
        return 'http://media.pearsoncmg.com/ph/streaming/esm/tanenbaum5e_videonotes/tanenbaum_videoNotes.html'
    
    def get_re(self):
        return r'.+\.m4v'

    def get_entity(self, rurl):
        page_contents = uriutils.fetch_page_contents(rurl)
        pq = pyquery.PyQuery(page_contents)
        video_source_re = r"\{'file':\s*'(?P<url>[^']+)'"
        match_res = re.search(video_source_re, pq('script').text())
        url = match_res.group('url')
        return super().get_entity(url)


def main():
    prog = os.path.basename(__file__)
    Tanenbaum5eVideoNotesCrawler(prog, __version__).run()

    
if __name__ == '__main__':
    main()
