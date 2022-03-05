#! /usr/bin/env python3
#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from dataclasses import dataclass
from pathlib import Path
import sys
from typing import List
import warnings

import fileutil


@dataclass
class CodeBlock:
    file_name: Path
    start_line_no: int
    end_line_no: int
    lang: str
    code: List[str]
    indent: int


CODE_BLOCK_MARKER = '```'


def iter_code_block(md_file: Path, encoding: str = None):
    assert md_file.exists(), f'Path "{md_file}" doesn\'t exist.'

    line_no = 0

    code_block = None
    indent = 0

    with md_file.open(encoding=encoding) as fp:
        for line in fp:
            line = line.rstrip('\n')
            line_no += 1

            pos = line.find(CODE_BLOCK_MARKER)

            if code_block is None:
                if pos == -1:
                    continue

                indent = pos
                lang = line[pos + len(CODE_BLOCK_MARKER):]

                pos2 = line.find(CODE_BLOCK_MARKER,
                                 pos + len(CODE_BLOCK_MARKER))
                if pos2 == -1:
                    code_block = CodeBlock(md_file, line_no + 1, -1, lang, [],
                                           indent)
            else:
                if pos == -1:
                    if len(line) < indent:
                        warnings.warn(
                            f'MarkDown code block syntax error in {md_file} at line {line_no}.',
                            UserWarning)

                    code_block.code.append(line[indent:])
                else:
                    code_block.end_line_no = line_no - 1
                    yield code_block

                    code_block = None


def main():
    search_path = Path(sys.argv[1]) if len(sys.argv) > 1 else Path.cwd()
    markdown_files = Path(search_path).rglob('*.md')

    for md in markdown_files:
        encoding = fileutil.detect_encoding(md)
        if not 'encoding' in encoding:
            print(f'Failed to detect encoding of file "{md}"')
            continue

        print(md, encoding)
        for code_block in iter_code_block(md, encoding['encoding']):
            code = '\n'.join(code_block.code)
            #print(code)

            code = code.strip()
            if not code:
                print(f'Found empty code block:\n{code_block}')
                input()


if __name__ == '__main__':
    main()

# References:
# [Recursively iterate through all subdirectories using pathlib](https://stackoverflow.com/questions/50714469/recursively-iterate-through-all-subdirectories-using-pathlib)
# [What are data classes and how are they different from common classes?](https://stackoverflow.com/questions/47955263/what-are-data-classes-and-how-are-they-different-from-common-classes)
# [Type hinting a collection of a specified type](https://stackoverflow.com/questions/24853923/type-hinting-a-collection-of-a-specified-type)
# https://www.markdownguide.org/extended-syntax/
# https://chardet.readthedocs.io/en/latest/
