# -*- coding: utf-8 -*-

# 2015-05-19T14:16+08:00

# List all available ports on your windows.

import pprint
import winreg

import RegKey

def main():
    key = winreg.HKEY_LOCAL_MACHINE
    sub_key = r'SOFTWARE\Microsoft\Windows NT\CurrentVersion\Ports'
    
    pprint.pprint(list(RegKey.EnumValue(key, sub_key)))

if __name__ == '__main__':
    main()
