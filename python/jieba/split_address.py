#!/usr/bin/env python3
# coding: utf-8
# $ yapf -i split_address.py

import os.path
import sys

import jieba
import openpyxl
import xlrd


app_dir = os.path.dirname(__file__)
excel_name = r'./04.01拓单订单（导入管家）.xls'
excel_path = os.path.join(app_dir, excel_name)

if not os.path.exists(excel_path):
    sys.exit(0)

# InvalidFileException: openpyxl does not support the old .xls file format, 
# please use xlrd to read this file, or convert it to the more recent .xlsx
# file format.
# workbook = openpyxl.open(excel_path)

workbook = xlrd.open_workbook(excel_path)
worksheet = workbook.sheets()[0]

addresses = []

for i, row in enumerate(worksheet.get_rows()):
    if i == 0:
        continue

    full_address = row[8].value
    parts = list(jieba.cut(row[8].value, cut_all=False, HMM=True))
    province, city, *remain = parts
    remain = ''.join(remain)
    print(province, city, remain)
    
    addresses.append((province, city, remain))

addessses_excel_name = r'addresses.xlsx'
addessses_excel_path = os.path.join(app_dir, addessses_excel_name)

if not os.path.exists(addessses_excel_path):
    workbook = openpyxl.Workbook()
    worksheet = workbook.active
    
    for addr in addresses:
        worksheet.append(addr)
    
    workbook.save(addessses_excel_path)
    workbook.close()


# References:
# [How to get row number in xlrd and save it into a variable](https://stackoverflow.com/questions/53523808/how-to-get-row-number-in-xlrd-and-save-it-into-a-variable)
