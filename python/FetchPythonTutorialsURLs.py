#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 2014-10-27 10:43 (UTC+8)

def main():
    import os
    import re
    import urllib.request

    response = urllib.request.urlopen('http://www.bogotobogo.com/python/pytut.php')
    page_encoding = response.headers.get_content_charset(failobj = 'utf-8')
    page_contents = response.read().decode(page_encoding)

    target_file = os.path.join(os.environ['HOME'], 'page.txt')
    with open(target_file, 'w') as fp:
        fp.write(page_contents)

    python_tutorial_urls = []
    url_pattern = re.compile(r'<a href="(.*)">')
    with open(target_file) as fp:
        # skip several lines until we reach the start line of <List of Python Tutorials>
        for line in iter(fp.readline, '<h1>List of Python Tutorials</h1>\n'):
            pass
        # 
        for line in iter(fp.readline, '<ul>\n'):
            pass
        #
        for line in iter(fp.readline, '</ul>\n'):
            search_res = url_pattern.search(line)
            if search_res:
                python_tutorial_urls.append(search_res.group(1))
    #
    os.remove(target_file)

    # Now, we got all the urls of <List of Python Tutorials>, process this list
    with open(os.path.join(os.environ['HOME'], 'List_of_Python_Tutorials.txt'), 'w') as fp:
        for url in python_tutorial_urls:
            print(url, file = fp)

if __name__ == '__main__':
    main()
    
