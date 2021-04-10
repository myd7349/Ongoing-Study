#!/usr/bin/env python3
# coding: utf-8

import plumbum

print(plumbum.local.cmd.tree())

notepad = plumbum.local[r'C:\Windows\notepad.exe']
notepad()

try:
    print(plumbum.local.cmd.ls())
except plumbum.CommandNotFound as ex:
    print(ex)
