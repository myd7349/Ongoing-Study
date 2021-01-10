# -*- coding: utf-8 -*-

import sys

import pywinauto
from pywinauto.application import Application

app_name = input('Please input app name > ')
app = Application().connect(path=app_name)

try:
    list1 = app.Dialog.List1
    if list1.item_count() >= 3:
        list1.item(2).select().click(double=True)
    
    print(app.Dialog.ListView1.wrapper_object())
    print(list1.wrapper_object())
except pywinauto.MatchError as e:
    sys.exit(e)


# References:
# https://pywinauto.readthedocs.io/en/latest/code/pywinauto.controls.common_controls.html
# [pywinauto and listitem selection](https://stackoverflow.com/questions/41112765/pywinauto-and-listitem-selection)
