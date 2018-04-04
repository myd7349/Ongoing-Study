# -*- coding: utf-8 -*-

# 2018-04-04T10:32+08:00

import os
import re

import dirwalker


sample_dir = r'C:\ADLINK\UDASK\samples\1901_02_03'
code_files = [file for file in dirwalker.ifile(sample_dir) if file.endswith('.cpp')]

for code_file in code_files:
    new_code_file = code_file + '.new'
    
    with open(code_file, 'rb') as fp:
        with open(new_code_file, 'wb') as fp2:
            for line in fp:
                if b'USB_1902' in line:
                    #match_res = re.match(b'(.*?[^A-Za-z0-9])(?<!case )USB_1902([^A-Za-z0-9].*)', line, re.DOTALL)
                    #new_line = match_res.group(1) + b'USB_1901' + match_res.group(2)
                    new_line = re.sub(rb'([^A-Za-z0-9])(?<!case )USB_1902([^A-Za-z0-9])', rb'\1USB_1901\2', line)
                    fp2.write(new_line)
                    print(line, '->', new_line)
                else:
                    fp2.write(line)
    
    os.remove(code_file)
    os.rename(new_code_file, code_file)
