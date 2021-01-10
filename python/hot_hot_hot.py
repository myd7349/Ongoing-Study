#!/usr/bin/env python3
# coding: utf-8

# A few days ago, one laoge shared some archives in
# a wechat group. When he created these archives
# with Bandizip on MacOS, he used chinese characters
# "人鱼" as the password.
#
# Because of encoding difference on different PCs, I
# failed to decompress these files with "人鱼" on my
# Win10 PC with Bandizip.
# Instead, I should use "浜洪奔" as the password.

pwd = '人鱼'
pwd_utf8 = pwd.encode('utf-8')

print(pwd_utf8)
print(pwd_utf8.decode('gbk'))


# Output:
# b'\xe4\xba\xba\xe9\xb1\xbc'
# '浜洪奔'

# References:
# [压缩包使用中文密码带来的问题 - DDKK64 - 博客园](https://www.cnblogs.com/wyzersblog/p/13882302.html)
