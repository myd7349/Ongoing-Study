#!/usr/bin/env python3
# coding: utf-8

import re
import webbrowser

articles = (
    '[谈编程语言互操作-概述](https://zhuanlan.zhihu.com/p/281059891)',
    '[谈编程语言互操作-C/C++互操作机制](https://zhuanlan.zhihu.com/p/291400029)',
    '[谈编程语言互操作-Java/C++互操作机制](https://zhuanlan.zhihu.com/p/297727926)',
    '[谈编程语言互操作-Java/Kotlin互操作机制](https://zhuanlan.zhihu.com/p/299669161)',
)

for article in articles:
    article_url = re.search(r'\((.*)\)', article)[1]
    webbrowser.open(article_url, new=2)
