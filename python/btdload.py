#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2016-01-01T14:56+08:00
# Happy New Year!

import functools
import re
import sys
import urllib.parse

import bs4

import bshelper


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


class SearchPred:
    def __init__(self,
                 page_no_pred=None,
                 count_pred=None,
                 movie_item_pred=None):
        self.page_no_pred = page_no_pred
        self.count_pred = count_pred
        self.movie_item_pred = movie_item_pred


_url = functools.partial(urllib.parse.urljoin, 'http://www.bttiantang.com/')


def _movie_item(item_soup: bs4.element.Tag) -> MovieItem:  
    litpic_soup = item_soup.find('div', attrs={'class': 'litpic'})
    title_soup = item_soup.find('div', attrs={'class': 'title'})

    title_p_soups = title_soup.find_all('p')

    litpic_url = litpic_soup.a.img['src']
    subject_url = _url(litpic_soup.a['href'])
    title = title_p_soups[0].b.getText()
    other = title_p_soups[1].a.getText()
    info = title_p_soups[2].getText()
    star = title_p_soups[3].getText()

    return MovieItem(litpic_url, subject_url, title, other, info, star)


def _get_ml_soup(*args, **kwargs):
    r, soup = bshelper.get_r_soup(*args, **kwargs)
    return r, soup.find('div', attrs={'class': 'ml'})


def _page_list(title: str):
    r, ml_soup = _get_ml_soup(_url('/s.php'), params={'q': title})
    
    # When searching with some big words like "爱情", the html content we
    # see in the Chrome Developer Tools may be looked like this:
    #     <ul class="pagelist cl">
    #       <form action="/s.php" name="pagelist">
    #         ...
    #       </form>
    #     </ul>
    # However, the case is that what BeautifulSoup4 got is:
    #     <ul class="pagelist cl"></ul>
    #     <form action="/s.php" name="pagelist">
    #       ...
    #     </form>
    statistic = ml_soup.find('ul', attrs={'class': 'pagelist cl'}).getText().strip()
    
    if statistic:
        # 心灵捕手
        # 心灵ad捕手
        # 大镖客
        pages, items = map(int, re.findall(r'\d+', statistic))
        print('Found {} items in {} pages.'.format(items, pages))
        
        assert pages in (0, 1)
        yield (1, r.url)
    else:
        # 蝙蝠侠
        # 爱情
        page_list_soup = ml_soup.find('form', attrs={'action': '/s.php', 'name': 'pagelist'})
        items, pages = map(int, re.findall(r'\d+', page_list_soup.li.getText()))
        print('Found {} items in {} pages.'.format(items, pages))

        li_soups = page_list_soup.find_all('li')
        first_href_with_qs = next(
            (li.a['href'] for li in page_list_soup.find_all('li') if li.find('a'))
            )
        pr = urllib.parse.urlparse(first_href_with_qs)
        qsl = urllib.parse.parse_qsl(pr.query)

        pr0 = urllib.parse.urlparse(_url(''))

        for page_no in range(1, pages+1):
            new_qsl = (qsl[0], (qsl[1][0], page_no))
            qs = urllib.parse.urlencode(new_qsl)
            new_pr = urllib.parse.ParseResult(pr0.scheme,
                                              pr0.netloc,
                                              pr.path,
                                              '',
                                              qs,
                                              '')
            yield (page_no, new_pr.geturl())


def search_movie(title: str, pred: SearchPred=SearchPred()): # ?? type hints for generator function?
    count = 0
    
    for page_no, page_url in _page_list(title):
        if not pred.page_no_pred or pred.page_no_pred(page_no):
            *_, ml_soup = _get_ml_soup(page_url)
            for item_soup in ml_soup.find_all('div', attrs={'class': 'item cl'}):
                if item_soup.find('div', 'title'):
                    count += 1
                    movie_item = _movie_item(item_soup)

                    if (not pred.count_pred or pred.count_pred(count)) and \
                       (not pred.movie_item_pred or pred.movie_item_pred(movie_item)):
                        yield (page_no, count, movie_item)


def retrieve_bt_urls(movie_item: MovieItem):
    *_, soup = bshelper.get_soup(movie_item.subject_url)
    for bt_soup in soup.find_all('div', attrs={'class': 'tinfo'}):
        yield _url(bt_soup.a['href'])
        


def dload_bt(movie_item: MovieItem, target_path: str):
    for bt_url in retrieve_bt_urls(movie_item):
        #r = requests.post(bt_url, data={'action': '/download1.php'})
        pass


def main():
    pred = SearchPred(count_pred=lambda c: c<=50)
    sys.argv.append('大镖客')
    for movie_title in sys.argv[1:]:
        for page_no, count, movie_item in search_movie(movie_title, pred):
            print(page_no, count, movie_item)
            #dload_bt(movie_item, '')
            pass


if __name__ == '__main__':
    main()
