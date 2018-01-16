#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-01-16T10:12+08:00

import pyquery  # pip install pyquery

from FetchPythonTutorialsURLs import fetchPage as fetch_page


def fetch_page_contents(url, encoding='utf-8'):
    return ''.join(fetch_page(url, encoding))


def iurl(page_contents):
    pq = pyquery.PyQuery(page_contents)
    yield from (url.attrib.get('href') for url in pq('a') if url.attrib.get('href'))
        
        
# References:
# https://stackoverflow.com/questions/9535732/how-to-extract-all-the-urls-from-a-website
# http://pyquery.readthedocs.io/en/latest/
