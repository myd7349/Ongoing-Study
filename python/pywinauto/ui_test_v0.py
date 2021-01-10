# -*- coding: utf-8 -*-

import sys

import pywinauto
from pywinauto.application import Application

app_name = input('Please input app name > ')
app = Application(backend='uia').connect(path=app_name)

try:
    list1 = app.Dialog.List1
    if list1.item_count() >= 3:
        list1.item(2).select().double_click_input()
    
    print(app.Dialog.ListView1.wrapper_object())
    print(list1.wrapper_object())
except pywinauto.MatchError as e:
    sys.exit(e)


# References:
# [Is there a way to speed up pywinauto?](https://stackoverflow.com/questions/59358742/is-there-a-way-to-speed-up-pywinauto)
# [Any possibility to make backend uia faster](https://github.com/pywinauto/pywinauto/issues/256)
# [pywinauto and listitem selection](https://stackoverflow.com/questions/41112765/pywinauto-and-listitem-selection)
