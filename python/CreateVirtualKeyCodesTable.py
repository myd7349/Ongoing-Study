#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2016-11-24T15:41+08:00


import datetime
import functools
import re
import tokenize

import tabulate


quote = lambda exp: r'\({0}\)'.format(exp)
make_group = lambda exp: r'({0})'.format(exp)

vkcode_re = r'[0-9A-Fa-f]{2}H?'
quoted_vkcode_re = quote(vkcode_re)

vkcode_rng_re = '-'.join((make_group(vkcode_re), make_group(vkcode_re)))
quoted_vkcode_rng_re = quote(vkcode_rng_re)

vkcode_symbol_re = r'VK_[A-Z0-9_]+'
vkcode_line_re = ''.join((
    '^'
    '.*',
    ' ',
    tokenize.group(quoted_vkcode_re, quoted_vkcode_rng_re),
    '$',
    ))

alphanumeric_description_re = r'^([^ ]+) key$'


class VkCodeEntry:
    def __init__(self, id_=0, symbol='0', descriptions=None):
        self.id = id_
        self.symbol = symbol
        self.descriptions = descriptions
        if self.descriptions is None:
            self.descriptions = []

    def generate_code(self, defined=False):
        assert len(self.descriptions) >= 1, 'Didn\'t MSDN tell you what the meaning of this virtual-key code is???'

        code_lines = [('{0}{1},'.format('//' if defined else '', self.symbol),
                       '// {0}: {1}'.format(self.id, self.descriptions[0]))]
        for additional_desc in self.descriptions[1:]:
            code_lines.append((' ', '// ' + additional_desc))

        return code_lines

    def __lt__(self, entry):
        return self.id < entry.id

    def __eq__(self, entry):
        return self.id == entry.id
        
    def __str__(self):
        return tabulate.tabulate(self.generate_code(), tablefmt='plain')


class VkCodeSection:
    def __init__(self):
        self.reset()

    def __bool__(self):
        return bool(re.match(vkcode_line_re, self.vkcode_line))

    def __str__(self):
        return ''.join((self.vkcode_line, *self.descriptions))

    def reset(self):
        self.vkcode_line = None
        self.descriptions = []
        self.in_section = False

    def is_multiline_description(self):
        assert len(self.descriptions) > 0, 'Didn\'t MSDN tell you what the meaning of this virtual-key code is???'
        return len(self.descriptions) > 1

    def is_singleline_description(self):
        assert len(self.descriptions) > 0, 'Didn\'t MSDN tell you what the meaning of this virtual-key code is???'
        return len(self.descriptions) == 1

    def is_range(self):
        assert self.vkcode_line, 'Invalid section'
        return bool(re.search(quoted_vkcode_rng_re, self.vkcode_line))

    def is_reserved(self):
        return self.is_singleline_description() and self.descriptions[0].strip() == 'Reserved'

    def is_undefined(self):
        return self.is_singleline_description() and self.descriptions[0].strip() in ('Unassigned', 'Undefined')

    def feed_line(self, line):
        striped_line = line.rstrip()

        if re.match(vkcode_line_re, striped_line):
            if self.in_section:
                return False  # This line doesn't belong to this section, so do not process it.
            else:
                self.vkcode_line = line
                self.in_section = True
                return True  # This section is still not ended.
        else:
            if striped_line:
                assert self.in_section, 'Oops!'
                self.descriptions.append(line)
            return True

    def parse(self):
        assert self, 'Invalid section!'
        
        symbol = '0'
        
        if self.is_range():
            res = re.search(quoted_vkcode_rng_re, self.vkcode_line)
            assert res, 'Pardon me???'
            start_id, end_id = map(functools.partial(int, base=16), res.groups())
            
            for id_ in range(start_id, end_id+1):
                yield VkCodeEntry(id_, symbol, self.descriptions)
        else:
            res = re.search(vkcode_symbol_re, self.vkcode_line)
            if res:
                symbol = res.group(0)
            else:
                if not self.is_reserved() and not self.is_undefined():
                    res = re.search(alphanumeric_description_re, self.descriptions[0])
                    if res:
                        symbol = r"'{0}'".format(res.group(1))

            id_ = int(re.search(quoted_vkcode_re, self.vkcode_line).group(0)[1:3], base=16)

            yield VkCodeEntry(id_, symbol, self.descriptions)


def main():
    vkcode_sections = []

    # 1. Load all sections
    with open(r'MSDN_Virtual-Key Codes.txt', 'r', encoding='ascii') as fp:
        lines = fp.readlines()
        lines_count = len(lines)
        
        i = 0
        section = VkCodeSection()
        
        while i < lines_count:
            is_section_continuing = section.feed_line(lines[i])
            
            if not is_section_continuing:
                vkcode_sections.append(section)
                
                section = VkCodeSection()
                is_section_continuing = section.feed_line(lines[i])
                assert is_section_continuing, 'Bad section!'

            i += 1

        # The last section
        if section:
            vkcode_sections.append(section)
    
    # 2. Parse all sections
    vkcode_entries = [VkCodeEntry(descriptions=['-'])]
    vkcode_entries.extend(entry
                          for section in vkcode_sections
                          for entry in section.parse()
                          )
    
    # 3. Generate Virtual-Key Codes Table
    code_lines = []
    already_defined_vkcodes = set()

    for entry in vkcode_entries:
        code_lines.extend(entry.generate_code(defined=entry.id in already_defined_vkcodes))
        already_defined_vkcodes.add(entry.id)

    # 4. At last...
    print('/* Generated by "CreateVirtualKeyCodesTable.py" at {0} */'.format(datetime.datetime.now().isoformat()))
    print('static unsigned char VkCodesTable[] = {')
    indent = ' ' * 4
    for line in tabulate.tabulate(code_lines, tablefmt='plain').splitlines():
        print(indent + line)
    print('};')


if __name__ == '__main__':
    main()

# References:
# Ongoing-Study/cpp/Win32/SDK/VkHelper
