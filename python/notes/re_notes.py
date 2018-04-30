#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import re
import tokenize


# 2016-08-13T23:28+08:00
# From Chromium depo tools/scm.py
def ValidateEmail(email):
    return (re.match(r"^[a-zA-Z0-9._%-+]+@[a-zA-Z0-9._%-]+.[a-zA-Z]{2,6}$", email) is not None)


# 2017-12-29T14:16+08:00
int_0_255_re = tokenize.group(r'(\d{1,2})|(1\d\d)|(2[0-4]\d)|(25[0-5])')
ipv4_re = '^' + tokenize.group(int_0_255_re + '.') + r'{3}' + int_0_255_re + '$'

# References:
# Sams Teach Yourself Regular Expressions in 10 Minutes
def ValidateIPv4(ip_addr):
    return (re.match(ipv4_re, ip_addr) is not None)


# References:
# https://github.com/Microsoft/vcpkg/blob/master/toolsrc/src/vcpkg/base/files.cpp#L9
def ValidateFileName(filename):
    return (re.match(r'[^\[\/:*?"<>|\]]+', filename) is not None)


# References:
# https://github.com/kevva/base64-regex/blob/master/index.js
def ValidateBase64(text):
    pass

