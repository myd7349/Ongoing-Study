#!/usr/bin/env python3
# coding: utf-8
# $ yapf -i split_address.py

import os.path
import sys

import openpyxl
import snownlp
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

addresses = []

for i, row in enumerate(worksheet.get_rows()):
    if i == 0:
        continue

    full_address = row[8].value
    parts = snownlp.SnowNLP(full_address).words

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
