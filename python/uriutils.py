#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-01-16T10:12+08:00

import urllib.request

import pyquery  # pip install pyquery


# UA definition shamelessly stolen from https://github.com/kennethreitz/requests-html/blob/master/requests_html.py
DEFAULT_USER_AGENT = 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_6) AppleWebKit/603.3.8 (KHTML, like Gecko) Version/10.1.2 Safari/603.3.8'


def fetch_page(url, encoding='utf-8'):
    request = urllib.request.Request(url, headers={'User-Agent': DEFAULT_USER_AGENT})
    response = urllib.request.urlopen(request)
    
    if encoding:
        charset = response.headers.get_content_charset(failobj = encoding)
        for line in response:
            yield line.decode(charset)
    else:
        yield from response


def fetch_page_contents(url, encoding='utf-8'):
    return ''.join(fetch_page(url, encoding))


def iurl(page_contents):
    pq = pyquery.PyQuery(page_contents)
    yield from (url.attrib.get('href') for url in pq('a') if url.attrib.get('href'))
        
        
# References:
# https://stackoverflow.com/questions/9535732/how-to-extract-all-the-urls-from-a-website
# http://pyquery.readthedocs.io/en/latest/
# https://stackoverflow.com/questions/802134/changing-user-agent-on-urllib2-urlopen
