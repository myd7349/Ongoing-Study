#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-04-12T12:04+08:00

import csv
import io


csv_content = '''Name,Age
Tom,2
Jerry,1
Tony,20
'''


def years(age: int) -> str:
    return f"year{'s' if age > 1 else ''}"


with io.StringIO(csv_content) as fp:
    reader = csv.DictReader(fp)
    for row in reader:
        print(f"{row['Name']} is {row['Age']} {years(int(row['Age']))} old.")


# References:
# Web Scraping with Python: Collecting Data from the Modern Web
