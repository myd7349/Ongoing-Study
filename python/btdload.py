#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2016-01-01T14:56+08:00
# Happy New Year!

import re
import sys
import urllib.parse

import bs4
import requests


class MovieItem:
    def __init__(self, litpic_url, subject_url, title, other, info, star):
        self.litpic_url = litpic_url
        self.subject_url = subject_url
        self.title = title
        self.other = other
        self.info = info
        self.star = star

    def __str__(self):
        return '{self.title}\n{self.other}\n{self.info}\n{self.star}'.format(self=self)


_root_url = 'http://www.bttiantang.com/'


def _movie_item(item_soup: bs4.element.Tag) -> MovieItem:  
    litpic_soup = item_soup.find('div', attrs={'class': 'litpic'})
    title_soup = item_soup.find('div', attrs={'class': 'title'})

    title_p_soups = title_soup.find_all('p')

    litpic_url = litpic_soup.a.img['src']
    subject_url = urllib.parse.urljoin(_root_url, litpic_soup.a['href'])
    title = title_p_soups[0].b.getText()
    other = title_p_soups[1].a.getText()
    info = title_p_soups[2].getText()
    star = title_p_soups[3].getText()

    return MovieItem(litpic_url, subject_url, title, other, info, star)


def search_movie(title: str): # ?? type hints for generator function?
    query_url = urllib.parse.urljoin(_root_url, 's.php')
    
    r = requests.get(query_url, params={'q': title})
    r.raise_for_status()

    soup = bs4.BeautifulSoup(r.content, 'html.parser')
    ml_soup = soup.find('div', attrs={'class': 'ml'})
    
    statistic = ml_soup.find('ul', attrs={'class': 'pagelist cl'})
    pages, items = re.findall(r'\d+', statistic.getText())

    if int(items) > 0:
        for item_soup in ml_soup.find_all('div', attrs={'class': 'item cl'}):
            if item_soup.find('div', 'title'):
                yield _movie_item(item_soup)
    

def retrieve_bt_urls(movie_item: MovieItem):
    r = requests.get(movie_item.subject_url)
    r.raise_for_status()

    soup = bs4.BeautifulSoup(r.content, 'html.parser')
    for bt_soup in soup.find_all('div', attrs={'class': 'tinfo'}):
        yield urllib.parse.urljoin(_root_url, bt_soup.a['href'])
        


def dload_bt(movie_item: MovieItem, target_path: str):
    for bt_url in retrieve_bt_urls(movie_item):
        r = requests.post(bt_url, data={'action': '/download1.php'})
        print(r.text)
        input()


def main():
    sys.argv.append('心灵捕手')
    for movie_title in sys.argv[1:]:
        for movie_item in search_movie(movie_title):
            print(movie_item)
            dload_bt(movie_item, '')


if __name__ == '__main__':
    main()
