#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-02-25T11:46+08:00

import os
import os.path
import sys
import urllib.error
import urllib.parse
import urllib.request

import bs4


__all__ = ['FetchPageError', 'fetch_html', 'ires', 'fetch_page']


class FetchPageError(Exception):
    def __init__(self, url):
        self.url = url

    def __str__(self):
        return '<FetchPageError: {0}>'.format(self.url)


def fetch_html(url, decode=False, encoding='utf-8'):
    try:
        response = urllib.request.urlopen(url)
        contents = response.read()

        if decode:
            charset = response.headers.get_content_charset(failobj=encoding)
            contents = contents.decode(charset)

        return contents 
    except (urllib.error.HTTPError, urllib.error.URLError) as exc:
        raise FetchPageError(url) from exc
    except UnicodeDecodeError as exc:
        raise FetchPageError(url) from exc


def ires(html, **tags):
    soup = bs4.BeautifulSoup(html, 'lxml')
    for tag in soup.findAll(tags.keys()):
        attr = tags[tag.name]
        assert attr, 'Invalid attribute!'
        if attr in tag.attrs:
            yield tag[attr]


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
    if not _make_dirs(target_dir):
        return

    target_dir = os.path.abspath(target_dir)

    html = fetch_html(url)
    html_subdir, html_fname = urllib.parse.urlsplit(url).path.rsplit('/', maxsplit=1)
    if not html_fname:
        html_fname = 'index.html'
    html_dir = os.path.join(target_dir, html_subdir[1:]) if html_subdir else target_dir
    html_fullpath = os.path.join(html_dir, html_fname)

    if not _make_dirs(html_dir):
        return

    # Save .html file.
    with open(html_fullpath, 'wb') as fp:
        fp.write(html)

    print('Save page "{0}" as "{1}".'.format(url, html_fullpath))

    if html_only:
        return

    # Save other resources
    for res in ires(html, img='src'):
        res_subdir, res_fname = res.rsplit('/', maxsplit=1)[-2:]
        res_dir = os.path.normpath(os.path.join(html_dir, res_subdir))

        if _make_dirs(res_dir):
            res_fullpath = os.path.join(res_dir, res_fname)
            res_uri = urllib.parse.urljoin(url, res)
            urllib.request.urlretrieve(res_uri, res_fullpath)
            print('Save "{0}" as "{1}".'.format(res_uri, res_fullpath))


if __name__ == '__main__':
    url = 'http://www.pythonscraping.com/pages/page3.html'
    fetch_page(url, '.\\temp', False)


# References:
# https://stackoverflow.com/questions/696047/re-raise-exception-with-a-different-type-and-message-preserving-existing-inform
