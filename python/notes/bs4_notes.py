#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-02-24T16:32+08:00


import bs4

html = '''
<html>
    <head>
        <title>A Useful Page</title>
    </head>

    <body>
        <h1>An Interesting Title</h1>

        <div>
        Hello, world!
        </div>
    </body>
</html>
'''

soup = bs4.BeautifulSoup(html, 'lxml')

split = '\n' + '-' * 80 + '\n'

print2nl = lambda *args, **kwargs: print(*args, **kwargs, end=split)

print2nl(soup.html)
print2nl(soup.head)
print2nl(soup.title)
print2nl(soup.body)
print2nl(soup.div)

print2nl(soup.h1)
print2nl(soup.body.h1)
print2nl(soup.html.body.h1)


# References:
# Web Scraping with Python By Ryan Mitchell
