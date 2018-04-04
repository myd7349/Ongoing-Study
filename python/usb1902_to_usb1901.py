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
                match_res = re.match(b'(.*?[^A-Za-z0-9])(USB_1902)([^A-Za-z0-9].*?)', line)
                if match_res:
                    fp2.write(match_res.group(1)+b'USB_1901'+match_res.group(3))
                    print(code_file, line)
                else:
                    fp2.write(line)
    
    os.remove(code_file)
    os.rename(new_code_file, code_file)
