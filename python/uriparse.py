#! /usr/bin/env python3
# -*- coding: utf-8 -*-
# 2014-01-19T19:39+08:00
# http://blog.csdn.net/ubiter/article/details/19809145

from re import compile as re_compile

_percent_pat = re_compile(b'((?:%[A-Fa-f0-9]{2})+)')
_unreserved_chars = frozenset(b'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
                              b'abcdefghijklmnopqrstuvwxyz'
                              b'0123456789'
                              b'_.-')

# A simple implement of  "urllib.parse.unquote"
def percent_decode(string, encoding = 'utf-8', errors = 'replace'):
    str_bytes = string.encode('utf-8')
    hex_to_byte = lambda match_ret: \
                  bytes.fromhex(
                      match_ret.group(0).replace(b'%', b'').decode('utf-8'))
    str_bytes = _percent_pat.sub(hex_to_byte, str_bytes)
    string = str_bytes.decode(encoding, errors)
    return string

# A simple implement of "urllib.parse.unquote_plus"
def percent_decode_plus(string, encoding = 'utf-8', errors = 'replace'):
    return percent_decode(string.replace('+', '%20'), encoding, errors)

# A simple implement of "urllib.parse.quote"
def percent_encode(string, safe = '/', encoding = 'utf-8', errors = 'strict'):
    if not string:
        return string
    string = string.encode(encoding, errors)
    bytes_unchanged = _unreserved_chars.union(
        safe.encode('ascii', 'ignore'))
    process_byte = lambda byte: chr(byte) if byte in bytes_unchanged \
                   else '%{:02X}'.format(byte)
    return ''.join((process_byte(b) for b in string))

# A simple implement of "urllib.parse.quote_plus"
def percent_encode_plus(string, safe = '', encoding = 'utf-8',
                        errors = 'strict'):
    safe += ' '
    string = percent_encode(string, safe, encoding, errors)
    return string.replace(' ', '+')

if __name__ == '__main__':
    import unittest
    import urllib.parse

    class TestURIParse(unittest.TestCase):
        def setUp(self):
            pass
        def tearDown(self):
            pass
        def doTest(self, str_, str_with_space, encoding_list):
            for en in encoding_list:
                # print('Test encoding:', en)

                str_enc = percent_encode(str_, encoding = en)
                self.assertEqual(
                    str_enc, urllib.parse.quote(str_, encoding = en))

                str_with_space_enc = percent_encode_plus(
                    str_with_space, encoding = en)
                self.assertEqual(
                    str_with_space_enc,
                    urllib.parse.quote_plus(str_with_space, encoding = en))

                # print('Test decoding:', en)
                self.assertEqual(percent_decode(str_enc, encoding = en),
                                 urllib.parse.unquote(str_enc, encoding = en))
                self.assertEqual(
                    percent_decode(str_with_space_enc, encoding = en),
                    urllib.parse.unquote(str_with_space_enc, encoding = en))
                self.assertEqual(
                    percent_decode_plus(str_with_space_enc, encoding = en),
                    urllib.parse.unquote_plus(
                        str_with_space_enc, encoding = en))
        def testChinese(self):
            fn = 'Beyond-海阔天空'
            fn_with_space = 'Beyond 海 阔 天 空'
            encoding_list = ('utf-8', 'gb2312', 'gbk', 'utf-16', 'utf-16-le',
                             'utf-16-be', 'utf-32', 'utf-32-le', 'utf-32-be',
                             'gb18030')
            self.doTest(fn, fn_with_space, encoding_list)
        def testReservedChars(self):
            reserved_chars = "!*'();:@&=+$,/?#[]"
            encoding_list = ('utf-8', 'gb2312', 'gbk', 'utf-16', 'utf-16-le',
                             'utf-16-be', 'utf-32', 'utf-32-le', 'utf-32-be',
                             'gb18030')
            self.doTest(reserved_chars, reserved_chars, encoding_list)
        def testEmptyString(self):
            self.doTest('', '', ('utf-8', 'utf-16-be', 'utf-32-le'))
        def testURL(self):
            url = 'http://www.baidu.com/'
            url_with_space = 'http://www.baidu.com/黑 客 帝 国.rmvb'
            encoding_list = ('utf-8', 'gb2312', 'gbk', 'utf-16', 'utf-16-le',
                             'utf-32', 'utf-32-le', 'gb18030')
            self.doTest(url, url_with_space, encoding_list)
        def testFileName(self):
            file_name = '%5B%E9%81%93%E5%BE%B7%E6%83%85%E6%93%8D%E8%AE%BA%5D.%E4%B8%AD%E5%A4%AE%E7' \
                        '%BC%96%E8%AF%91%E5%87%BA%E7%89%88%E7%A4%BE%EF%BC%88%E8%B0%A2%E5%AE%97%E6%9E' \
                        '%97%E8%AF%91%29'
            self.assertEqual(percent_decode(file_name),
                             urllib.parse.unquote(file_name))
        def testRealURL(self):
            wiki_page = 'http://zh.wikipedia.org/wiki/%E7%99%BE%E5%88%86%E5%8F%B7%E7%BC%96%E7%A0%81'
            self.assertEqual(percent_decode(wiki_page),
                             urllib.parse.unquote(wiki_page))
                
    unittest.main()


# References:
# https://www.codeproject.com/Articles/7828/CHttpClient-A-Helper-Class-Using-WinInet
# https://github.com/ProgerXP/Notepad2e/blob/master/src/Extension/StrToURL.c
