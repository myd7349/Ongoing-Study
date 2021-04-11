#!/usr/bin/env python3
# coding: utf-8
# $ yapf -i split_address.py

import os.path
import sys

import cpca
import xlrd


app_dir = os.path.dirname(__file__)
excel_name = r'../jieba/orders.xls'
excel_path = os.path.join(app_dir, excel_name)

if not os.path.exists(excel_path):
    sys.exit(0)

# InvalidFileException: openpyxl does not support the old .xls file format, 
# please use xlrd to read this file, or convert it to the more recent .xlsx
# file format.
# workbook = openpyxl.open(excel_path)

workbook = xlrd.open_workbook(excel_path)
worksheet = workbook.sheets()[0]

full_addresses = []

for i, row in enumerate(worksheet.get_rows()):
    if i == 0:
        continue

    full_addresses.append(row[8].value)

result = cpca.transform(full_addresses)
print(result)


addessses_excel_name = r'addresses.xlsx'
addessses_excel_path = os.path.join(app_dir, addessses_excel_name)

if not os.path.exists(addessses_excel_path):
    result.to_excel(addessses_excel_path)


# References:
# [How to get row number in xlrd and save it into a variable](https://stackoverflow.com/questions/53523808/how-to-get-row-number-in-xlrd-and-save-it-into-a-variable)
# [使用python提取中文地址描述中的省市区信息](https://blog.csdn.net/qq_33256688/article/details/79445792)
