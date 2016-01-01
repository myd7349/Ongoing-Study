#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2016-01-01T14:56+08:00
# Happy New Year!

import re
import sys
import urllib.parse

import bs4
import requests


class BTDloadError(Exception): pass


class MovieItem:
    def __init__(self, litpic_url, bt_url, title, other, info, star):
        self._litpic_url = litpic_url
        self._bt_url = bt_url
        self._title = title
        self._other = other
        self._info = info
        self._star = star

    def __str__(self):
        return '{self._title}\n{self._other}\n{self._info}\n{self._star}'.format(self=self)


_root_url = 'http://www.bttiantang.com/'


def _movie_item(item_soup: bs4.element.Tag) -> MovieItem:  
    litpic_soup = item_soup.find('div', attrs={'class': 'litpic'})
    title_soup = item_soup.find('div', attrs={'class': 'title'})

    title_p_soups = title_soup.find_all('p')

    litpic_url = litpic_soup.a.img['src']
    bt_url = urllib.parse.urljoin(_root_url, litpic_soup.a['href'])
    title = title_p_soups[0].b.getText()
    other = title_p_soups[1].a.getText()
    info = title_p_soups[2].getText()
    star = title_p_soups[3].getText()

    return MovieItem(litpic_url, bt_url, title, other, info, star)


def search_bt(title: str) -> str:
    query_url = urllib.parse.urljoin(_root_url, 's.php')
    
    r = requests.get(query_url, params={'q': title})
    r.raise_for_status()

    soup = bs4.BeautifulSoup(r.content, 'html.parser')
    ml_soup = soup.find('div', attrs={'class': 'ml'})
    
    statistic = ml_soup.find('ul', attrs={'class': 'pagelist cl'})
    pages, items = re.findall(r'\d+', statistic.getText())

    if items == 0:
        raise BTDloadError('No BTs found for "{}"'.format(title))
    else:
        for item_soup in ml_soup.find_all('div', attrs={'class': 'item cl'}):
            if item_soup.find('div', 'title'):
                item = _movie_item(item_soup)
                print(item)

    return r.url
    

def get_bt(title):
    search_bt(title)


def main():
    sys.argv.append('窃听风暴')
    for movie_title in sys.argv[1:]:
        get_bt(movie_title)


if __name__ == '__main__':
    main()
