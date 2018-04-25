# -*- coding: utf-8 -*-
# 2013-12-17 15:20

import re

class ParseRCError(Exception):
    def __init__(self, file_name, line_no, msg = ''):
        self._file_name = file_name
        self._line_no = line_no
        self._msg = msg
        
    def __str__(self):
        msg = 'Parse RC file failed: {0}({1:d}). {2}. {3}' \
              .format(self._file_name, self._line_no, self._msg)
        return msg

class StringTableIterator:
    '''Iterate all the string entries in the string tables of RC file.'''
    def __init__(self, rc_file, enc):
        try:
            self._fid = open(rc_file, 'r', encoding = enc)
        except IOError:
            self._fid = None

        self._stat = {'STRINGTABLE': False, 'BEGIN': False}
        self._init_stat()

        # Though it it too simple to parse all the STRINGTABLEs in arbitrary
        # RC files, it is enough for me to finish my work.
        self._str_tb_marker_pat = re.compile(r'^[ \t]*STRINGTABLE[ \t]*\n$')
        self._str_tb_begin_pat = re.compile(r'^[ \t]*BEGIN[ \t]*\n$')
        self._str_tb_end_pat = re.compile(r'^[ \t]*END[ \t]*\n?$')
        self._str_id_search_re = r'^[ \t]*(?P<STR_ID>[A-Za-z_][A-Za-z0-9_]*)' + \
                                 r'[ \t]*"(?P<STR>.*)"'
        self._str_id_search_pat = re.compile(self._str_id_search_re)

        self._rc_file = rc_file
        self._line_no = 0

    def __del__(self):
        self.close()
        
    def __iter__(self):
        return self
    
    def __next__(self):
        if self._fid:
            if not self._stat['STRINGTABLE']:
                for line in self._fid: # TODO: Handle potential exception
                    self._line_no += 1
                    if self._str_tb_marker_pat.search(line):
                        self._stat['STRINGTABLE'] = True
                        break

                if not self._stat['STRINGTABLE']:
                    self.close()
                    raise StopIteration

            if self._stat['STRINGTABLE'] and not self._stat['BEGIN']:
                for line in self._fid: # TODO: Handle potential exception
                    self._line_no += 1
                    if self._str_tb_begin_pat.search(line):
                        self._stat['BEGIN'] = True
                        break

                if not self._stat['BEGIN']:
                    raise ParseRCError(self._rc_file, self._line_no)
            
            if self._stat['STRINGTABLE'] and self._stat['BEGIN']:
                for line in self._fid: # TODO: Handle potential exception
                    self._line_no += 1
                    str_id_search_ret = self._str_id_search_pat.search(line)
                    if str_id_search_ret:
                        return (str_id_search_ret.group('STR_ID'),
                                str_id_search_ret.group('STR'))
                    elif self._str_tb_end_pat.search(line):
                        self._init_stat()
                        break

                if not self._stat['STRINGTABLE'] and not self._stat['BEGIN']:
                    return self.__next__() # Magic, isn't it? The GOD knows why.
                else:
                    raise ParseRCError(self._rc_file, self._line_no)
        else:
            raise StopIteration

    def _init_stat(self):
        self._stat['STRINGTABLE'] = False
        self._stat['BEGIN'] = False
        
    def close(self):
        if self._fid:
            self._fid.close()
            self._fid = None
            self._line_no = 0
            self._init_stat()

class StringIDIterator:
    def __init__(self, file_name, enc):
        self._file_name = file_name

        try:
            self._fid = open(file_name, encoding = enc)
        except IOError:
            self._fid = None

        self._search_re = r'^[ \t]*#define[ \t]+' + \
                          r'(?P<STR_ID>[A-Za-z_][A-Za-z0-9_]*)[ \t]+' + \
                          r'(?P<ID>(?P<HEX>0[xX])?(?(HEX)[0-9A-Fa-f]+|[0-9]+))' + \
                          r'[ \t]*.*\n?$'
        self._search_pat = re.compile(self._search_re)

    def __del__(self):
        self.close()

    def __iter__(self):
        return self

    def __next__(self):
        if self._fid:
            for line in self._fid:  # TODO: Handle potential exception
                search_ret = self._search_pat.search(line) 
                if search_ret:
                    return search_ret.group('STR_ID'), \
                           search_ret.group('ID')

            self.close()
            raise StopIteration
        else:
            raise StopIteration
    
    def close(self):
        if self._fid:
            self._fid.close()
            self._fid = None

class ControlIDIterator:
    def __init__(self, rc_file, enc):
        self._file_name = rc_file
        self._line_no = 0

        try:
            self._fid = open(rc_file, encoding = enc)
        except:
            self._fid = None
            
        self._begin_pat = re.compile(r'^[ \t]*BEGIN[ \t]*\n$')
        self._end_pat = re.compile(r'^[ \t]*END[ \t]*\n?$')
        
        # "((?P<ALPHA>[A-Z])|(?P<ALPHA>[a-z]))" can't be recognized by python.
        # "((?<ALPHA>[A-Z])|(?<ALPHA>[a-z]))" is accepted by a .NET RE engine.
        # So, if I want to search an alphabetic in a string:
        # 1. In .NET, use RE "((?<ALPHA>[A-Z])|(?<ALPHA>[a-z]))" and
        #    then just retrieve the group with name "ALPHA".
        # 2. In Python, use RE "((?P<ALPHA_0>[A-Z])|(?P<ALPHA_1>[a-z]))" and
        #    retrieve group "ALPHA_0" if it is not None, otherwise,
        #    retrieve group "ALPHA_1".
        self._ctrlid_re = r'^\s*(?:(?:CONTROL|CTEXT|DEFPUSHBUTTON|GROUPBOX' + \
                          r'|LTEXT|MENUITEM|PUSHBUTTON|RTEXT)' + \
                          r'|(?P<T0>COMBOBOX|EDITTEXT|LISTBOX))\s+' + \
                          r'(?(T0)(?P<CTRL_ID_0>[A-Za-z_][A-Za-z0-9_]*)|' + \
                          r'(?:".*"|[0-9]+)\s*,\s*' + \
                          r'(?P<CTRL_ID_1>[A-Za-z_][A-Za-z0-9_]*))'
        self._ctrlid_pat = re.compile(self._ctrlid_re)
        self._beg_cnt = 0

    def __del__(self):
        self.close()

    def __iter__(self):
        return self

    def __next__(self):
        if self._fid:
            for line in self._fid:
                self._line_no += 1
                if self._beg_cnt > 0:
                    ctrlid_search_ret = self._ctrlid_pat.search(line)
                    if ctrlid_search_ret:
                        if ctrlid_search_ret.group('CTRL_ID_0'):
                            return ctrlid_search_ret.group('CTRL_ID_0')
                        else:
                            return ctrlid_search_ret.group('CTRL_ID_1')
                    else:
                        if self._begin_pat.search(line):
                            self._beg_cnt += 1
                        elif self._end_pat.search(line):
                            self._beg_cnt -= 1
                elif self._beg_cnt == 0:
                    if self._begin_pat.search(line):
                        self._beg_cnt += 1
                else:
                    raise ParseRCError(self._file_name, self._line_no)

            if self._beg_cnt == 0:
                self.close()
                raise StopIteration
            else:
                raise ParseRCError(self._file_name, self._line_no)
        else:
            raise StopIteration

    def close(self):
        if self._fid:
            self._fid.close()
            self._fid = None
            self._line_no = 0
            self._beg_cnt = 0
