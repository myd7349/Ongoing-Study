#!/usr/bin/env python3
# coding: utf-8

import os
import os.path

import openpyxl

excel_name = 'openpyxl_delete_all_rows.xlsx'
excel_path = os.path.join(os.path.dirname(__file__), excel_name)

if not os.path.exists(excel_path):
    workbook = openpyxl.Workbook()
    worksheet = workbook.active

    for i in range(100):
        worksheet.append((i, ))

    workbook.save(excel_path)
    workbook.close()
else:
    workbook = openpyxl.open(excel_path)
    worksheet = workbook.active

    print(worksheet.min_row, worksheet.max_row)
    
    worksheet.delete_rows(worksheet.min_row, worksheet.max_row - worksheet.min_row + 1)

    #for i in reversed(range(worksheet.min_row, worksheet.max_row + 1)):
    #    worksheet.delete_rows(i)

    print(worksheet.min_row, worksheet.max_row)

    workbook.save(excel_path)
    workbook.close()

    os.remove(excel_path)


# References:
# [Python-Excel 模块哪家强？](https://zhuanlan.zhihu.com/p/23998083)
# [openpyxl - A Python library to read/write Excel 2010 xlsx/xlsm files](https://openpyxl.readthedocs.io/en/latest/)
# [Can't get OpenPyXl to delete rows](https://stackoverflow.com/questions/53376617/cant-get-openpyxl-to-delete-rows)
