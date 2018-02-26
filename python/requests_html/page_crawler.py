#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-02-26T15:00+08:00

import os
import os.path
import sys
import urllib.parse
import urllib.request

import requests_html  # pip install requests_html


class PageCrawler:
    def __init__(self, url):
        self.response = requests_html.session.get(url)

    @property
    def html(self):
        return self.response.text

    @property
    def links(self):
        return self.response.html.links

    @property
    def imgs(self):
        return self.response.html.find('img')


_p = lambda *args, **kwargs: print(*args, file=sys.stderr, **kwargs)


def _make_dirs(target_dir):
    if os.path.isdir(target_dir):
        return True

    try:
        os.makedirs(target_dir)
        print('Directory {0} is created.'.format(target_dir))
        return True
    except OSError as exc:
        _p(exc)

    return False


def fetch_page(url, target_dir, html_only=True):
    target_dir = os.path.abspath(target_dir)
    if not _make_dirs(target_dir):
        return

    crawler = PageCrawler(url)

    html = crawler.html
    html_subdir, html_fname = urllib.parse.urlsplit(url).path.rsplit('/', maxsplit=1)
    if not html_fname:
        html_fname = 'index.html'
    html_dir = os.path.join(target_dir, html_subdir[1:]) if html_subdir else target_dir
    html_fullpath = os.path.join(html_dir, html_fname)

    if not _make_dirs(html_dir):
        return

    # Save .html file.
    with open(html_fullpath, 'w', encoding='utf-8') as fp:
        fp.write(html)

    print('Save page "{0}" as "{1}".'.format(url, html_fullpath))

    if html_only:
        return

    # Save images
    for img in crawler.imgs:
        src = img.attrs.get('src', None)
        if src:
            img_subdir, img_fname = src.rsplit('/', maxsplit=1)[-2:]
            img_dir = os.path.normpath(os.path.join(html_dir, img_subdir))

            if _make_dirs(img_dir):
                img_fullpath = os.path.join(img_dir, img_fname)
                img_uri = urllib.parse.urljoin(url, src)
                urllib.request.urlretrieve(img_uri, img_fullpath)
                print('Save "{0}" as "{1}".'.format(img_uri, img_fullpath))


if __name__ == '__main__':
    url = 'http://www.pythonscraping.com/pages/page3.html'
    fetch_page(url, '.\\temp', False)


# References:
# Ongoing-study/python/fetch_page.py
