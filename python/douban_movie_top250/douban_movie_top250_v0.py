#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-05-23T16:23+08:00

# My first web crawler to get a list of TOP250 movies on douban.com,
# with BeautifulSoup4.

import datetime
import filecmp
import os
import os.path
import sys


history_dir = os.path.join(os.path.dirname(__file__), 'history')


def get_history_files():
    with os.scandir(history_dir) as it:
        for entry in it:
            if not entry.name.startswith('.') and entry.is_file():
                yield entry.name


def get_lastest_history_file_path():
    files = sorted(tuple(get_history_files()))
    return None if len(files) == 0 else os.path.join(history_dir, files[-1])


def main(file=sys.stdout):
    import urllib.request

    # BeautifulSoup4: https://pypi.python.org/pypi/beautifulsoup4/
    # pip install beautifulsoup4 (not `pip install beautifulsoup`)
    import bs4

    import tqdm

    try:
        import lxml
        lxml_installed = True
        del lxml
    except ImportError:
        lxml_installed = False

    start_url = 'https://movie.douban.com/top250'
    urls = [start_url]
    features = 'lxml' if lxml_installed else None
    
    with urllib.request.urlopen(start_url) as response:
        start_page = bs4.BeautifulSoup(response, features) # Use lxml's HTML parser if possible
        paginator = start_page.find('div', 'paginator')
        for page_href in paginator.find_all('a'):
            url = start_url + page_href.get('href')
            if url not in urls:
                urls.append(url)

    with tqdm.tqdm(total=250) as pbar:
        for url in urls:
            with urllib.request.urlopen(url) as response:
                soup = bs4.BeautifulSoup(response, features)
                movies_list = soup.find(id = 'content').ol
                for movie_item in movies_list:
                    if isinstance(movie_item, bs4.element.Tag):
                        movie_no = int(movie_item.em.string)
                        movie_title = movie_item.find('span', 'title').string
                        print('{:03d}: {}'.format(movie_no, movie_title), file=file)
                        pbar.update(1)


if __name__ == '__main__':
    if len(sys.argv) <= 1:
        if not os.path.exists(history_dir):
            os.mkdir(history_dir)
        target_file_name = datetime.date.today().strftime('%y%m%d') + '.txt'
        target_file = os.path.join(history_dir, target_file_name)
    else:
        target_file = sys.argv[1]

    if not os.path.exists(target_file) or os.stat(target_file).st_size == 0:
        lastest_history_file = get_lastest_history_file_path()
        
        with open(target_file, 'w', encoding='utf-8') as fp:
            main(fp)

        if lastest_history_file:
            if filecmp.cmp(target_file, lastest_history_file):
                print(f'Nothing new compared with {lastest_history_file}.')
                os.remove(target_file)
    else:
        print(f"'{target_file}' already exists.")


# References:
# [Beautiful Soup Documentation](http://www.crummy.com/software/BeautifulSoup/bs4/doc/)
# [XPath](http://www.w3.org/TR/xpath/)
# https://gist.github.com/yihong0618/0073ef00129db3459e4b5b2814f0408f
