#! /usr/bin/env python3
# coding: utf-8

# 2014-04-29T11:54+08:00

# http://zhidao.baidu.com/question/552503011466248932.html

import re

# findall: Return all non-overlapping matches of pattern in string
print(re.findall(r'aba','cababadddd'))

# In order to do overlapping searching, we can use lookahead assertion.
print(re.findall(r'(?=(aba))','cababadddd'))

# References:
# [How to find overlapping matches with a regexp?](http://stackoverflow.com/questions/11430863/how-to-find-overlapping-matches-with-a-regexp)
# [Overlapping regex matches](http://stackoverflow.com/questions/15799332/overlapping-regex-matches)
# [Python regex find all overlapping matches?](http://stackoverflow.com/questions/5616822/python-regex-find-all-overlapping-matches)
