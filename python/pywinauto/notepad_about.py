# -*- coding: utf-8 -*-

"""
Created on Wed Jan  6 18:16:26 2021
@author: myd7349
"""

from pywinauto.application import Application

app = Application().start('notepad.exe')
app.UntitledNotepad.menu_select('帮助(&H)->关于记事本')
