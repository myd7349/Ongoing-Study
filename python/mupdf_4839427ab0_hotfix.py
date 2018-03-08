#! /usr/bin/env python3
# coding: utf-8

# 2018-03-08T21:44+08:00

# When building MuPDF from scratch on Windows 7 with VS2010 this afternoon, I encountered several compilation errors like this:
#   >..\..\generated\SourceHanSansCN-Regular.c(3452): fatal error C1091: compiler limit: string exceeds 65535 bytes in length
#    ......
# I found these pages:
#    https://stackoverflow.com/questions/22905316/fatal-error-compiler-limit-when-building-cimg
#    https://github.com/glfw/glfw/issues/1145
#    https://sourceforge.net/p/fuego/tickets/88/
# So what I need to do is replacing code like this:
#    const unsigned char fz_resources_fonts_sil_CharisSIL_B_cff[] =
#    "\x01\x00\x04\x03\x00\x01\x01\x01\x0f\x43\x68\x61\x72\x69\x73\x53\x49\x4c\x2d"
#    "\x42\x6f\x6c\x64\x00\x01\x01\x01\x5c\xf8\x10\x00\x1c\x08\xc5\x01\x1c\x08\xc6"
#    "\x02\x1c\x08\xc7\x03\xf8\x14\x04\xfb\xf2\x0c\x03\xf7\x0c\x0c\x04\x1c\xfa\x3d"
#    "\xfe\xd8\x1c\x18\x00\x1c\x0a\x28\x05\x1e\xa0\x00\x48\x82\x80\x98\x8f\x8b\x8b"
#      ......
#    "\x3c\x1d\x88\xf7\xb3\x25\x0a\xf7\x19\x0a\xf7\x13\x66\x0a\xfd\xfe\x72\x1d\x0b"
#    "\x45\x0a\xfa\xf6\x43\x0a\x0e"
#    ;
# with code like this:
#    const unsigned char fz_resources_fonts_sil_CharisSIL_B_cff[] =
#    {
#      '\x01', '\x00', '\x04', '\x03', '\x00', '\x01', '\x01', '\x01', '\x0f', '\x43', '\x68', '\x61', '\x72', '\x69', '\x73', '\x53', '\x49', '\x4c', '\x2d', 
#      '\x42', '\x6f', '\x6c', '\x64', '\x00', '\x01', '\x01', '\x01', '\x5c', '\xf8', '\x10', '\x00', '\x1c', '\x08', '\xc5', '\x01', '\x1c', '\x08', '\xc6', 
#      '\x02', '\x1c', '\x08', '\xc7', '\x03', '\xf8', '\x14', '\x04', '\xfb', '\xf2', '\x0c', '\x03', '\xf7', '\x0c', '\x0c', '\x04', '\x1c', '\xfa', '\x3d', 
#      '\xfe', '\xd8', '\x1c', '\x18', '\x00', '\x1c', '\x0a', '\x28', '\x05', '\x1e', '\xa0', '\x00', '\x48', '\x82', '\x80', '\x98', '\x8f', '\x8b', '\x8b',
#      ......
#      '\x3c', '\x1d', '\x88', '\xf7', '\xb3', '\x25', '\x0a', '\xf7', '\x19', '\x0a', '\xf7', '\x13', '\x66', '\x0a', '\xfd', '\xfe', '\x72', '\x1d', '\x0b', 
#      '\x45', '\x0a', '\xfa', '\xf6', '\x43', '\x0a', '\x0e', 
#    };


import os
import os.path
import re
import tempfile


quoted_hex_bytes_re = r'^"(\\x[0-9a-f]{2})+"$'


def split_by_length(seq, length):
    """Split a sequence into several shorter ones with the same size."""
    chunks, chunk_size = len(seq)//length*length, length
    return [seq[i:i+length] for i in range(0, chunks, chunk_size)]


def process_line(line):
    if re.match(quoted_hex_bytes_re, line):
        line = line.strip()[1:-1]  # "\x00\x01"\n -> \x00\x01
        return ''.join("'{0}', ".format(ch) for ch in split_by_length(line, 4))


def process_line_ex(line):
    line = process_line(line)
    if line:
        return '{indent}{0}\n'.format(line, indent='  ')
    

def process_file(file):
    temp_file_name = None
    
    with open(file, 'r') as fp:
        first_line = fp.readline()
        second_line = fp.readline()
        third_line = fp.readline()

        if not re.match(quoted_hex_bytes_re, third_line):
            print('Skip', file)
            return

        with tempfile.NamedTemporaryFile(mode='w', encoding='ascii', delete=False) as temp_file:
            temp_file_name = temp_file.name
            
            temp_file.write(first_line)
            temp_file.write(second_line)
            temp_file.write('{\n')
            temp_file.write(process_line_ex(third_line))

            for line in fp:
                processed_line = process_line_ex(line)
                if processed_line:
                    temp_file.write(processed_line)
                elif line[0] == ';':
                    temp_file.write('};')
                else:
                    print(line)

    if temp_file_name:
        os.remove(file)
        os.rename(temp_file_name, file)


if __name__ == '__main__':
    if not os.path.isdir('./include/mupdf'):
        raise SystemExit('Run this script in the mupdf directory.')

    target_dir = '.{0}generated'.format(os.sep)
    if not os.path.isdir(target_dir):
        raise SystemExit('Sub-directory \'{0}\' not found.'.format(target_dir))

    fonts_resource_files = (os.path.join(target_dir, file) for file in os.listdir(target_dir))
    for file in fonts_resource_files:
        print('Processing file', file)
        process_file(file)        
        


# https://stackoverflow.com/questions/13673060/split-string-into-strings-by-length
