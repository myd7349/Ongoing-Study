#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-05-23T16:23+08:00

# My first web crawler to get a list of TOP250 movies on douban.com,
# with BeautifulSoup4.
    
def main():
    import urllib.request

    # BeautifulSoup4: https://pypi.python.org/pypi/beautifulsoup4/
    # pip install beautifulsoup4 (not `pip install beautifulsoup`)
    import bs4

    try:
        import lxml
        lxml_installed = True
        del lxml
    except ImportError:
        lxml_installed = False

    start_url = 'http://movie.douban.com/top250'
    urls = [start_url]
    features = 'lxml' if lxml_installed else None
    
    with urllib.request.urlopen(start_url) as response:
        start_page = bs4.BeautifulSoup(response, features) # Use lxml's HTML parser if possible
        paginator = start_page.find('div', 'paginator')
        for page_href in paginator.find_all('a'):
            url = start_url + page_href.get('href')
            if url not in urls:
                urls.append(url)

    for url in urls:
        with urllib.request.urlopen(url) as response:
            soup = bs4.BeautifulSoup(response, features)
            movies_list = soup.find(id = 'content').ol
            for movie_item in movies_list:
                if isinstance(movie_item, bs4.element.Tag):
                    print('{:03d}: {}'.format(int(movie_item.em.string),
                                              movie_item.find('span', 'title').string))

if __name__ == '__main__':
    main()

# References:
# [Beautiful Soup Documentation](http://www.crummy.com/software/BeautifulSoup/bs4/doc/)
# [XPath](http://www.w3.org/TR/xpath/)
