#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2016-01-03T14:17+08:00

import bs4
import requests


_parser = None


def get_parser():
    global _parser
    
    if _parser is None:
        try:
            import lxml
            del lxml
            _parser = 'lxml'
        except ImportError:
            _parser = 'html.parser'

    return _parser


def get_r_soup(*args, **kwargs):
    r = requests.get(*args, **kwargs)
    r.raise_for_status()

    return r, bs4.BeautifulSoup(r.content, get_parser())
