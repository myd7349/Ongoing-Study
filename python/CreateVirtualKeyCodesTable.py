#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2016-11-24T15:41+08:00


import re
import tokenize


vkcode_re = r'[0-9A-Fa-f]{2}'
vkcode_rng_re = '-'.join((vkcode_re, vkcode_re))
quoted_vkcode_re = r'\({0}\)'.format(vkcode_re)
quoted_vkcode_rng_re = r'\({0}\)'.format(vkcode_rng_re)

vkcode_symbol_re = r'VK_[A-Z0-9_]+'
vkcode_line_re = ''.join((
    '^'
    '.*',
    ' ',
    tokenize.group(quoted_vkcode_re, quoted_vkcode_rng_re),
    '$',
    ))


class VkCodeEntry:
    def __init__(self, symbol='', id_=0, is_defined=False, comment=''):
        self.symbol = symbol
        self.id = id_
        self.is_defined = is_defined
        self.comment = comment


class VkCodeSection:
    def __init__(self):
        self.reset()

    def __bool__(self):
        return bool(self.vkcode_line)

    def __str__(self):
        return ''.join((self.vkcode_line, *self.descriptions))

    def reset(self):
        self.vkcode_line = None
        self.descriptions = []
        self.in_section = False

    def is_multiline_description(self):
        assert len(self.descriptions) > 0, 'Doesn\' MSDN tell you what the meaning of this virtual-key code is???'
        return len(self.descriptions) > 1

    def is_singleline_description(self):
        assert len(self.descriptions) > 0, 'Doesn\' MSDN tell you what the meaning of this virtual-key code is???'
        return len(self.descriptions) == 1

    def is_range(self):
        assert self.vkcode_line, 'Invalid section'
        return bool(re.search(quoted_vkcode_rng_re, self.vkcode_line))

    def is_reserved(self):
        return self.is_singleline_description() and self.descriptions[0].strip() == 'Reserved'

    def is_undefined(self):
        return self.is_singleline_description() and self.descriptions[0].strip() == 'Unassigned'

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
        
        vkcode_entries = []
        
        if self.is_range():
            pass
        else:
            entry = VkCodeEntry()


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
                if __debug__:
                    print(section.is_reserved(), section.vkcode_line, end='')
                
                section = VkCodeSection()
                is_section_continuing = section.feed_line(lines[i])
                assert is_section_continuing, 'Bad section!'

            i += 1

        # The last section
        if section:
            vkcode_sections.append(section)

    # 2. Parse all sections
    vkcode_entries = []



if __name__ == '__main__':
    main()
