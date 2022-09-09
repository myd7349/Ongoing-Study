# coding: utf-8

import codecs

for m in dir(codecs):
    if m.startswith('BOM'):
        print(m, getattr(codecs, m))


# References:
# [Python - Decode UTF-16 file with BOM](https://stackoverflow.com/questions/22459020/python-decode-utf-16-file-with-bom)
