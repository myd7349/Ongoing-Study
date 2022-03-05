# coding: utf-8

import abc
import argparse
from typing import List

import cppmangle
import parse
import plumbum


class SymbolsExporter(abc.ABC):
    @abc.abstractmethod
    def export(self, dll_path: str) -> List[str]:
        pass


class DumpBin(SymbolsExporter):
    def __init__(self, tool: str):
        if tool == 'dumpbin':
            self._tool = 'dumpbin.exe'
        else:
            self._tool = tool

    def export(self, dll_path: str) -> List[str]:
        mangled_symbols = []
        start_line = 'ordinal hint RVA      name'
        start = False
        first_empty_line_after_start_line = True

        try:
            dumpbin = plumbum.local[self._tool]
            dll_exports = dumpbin('/EXPORTS', dll_path).splitlines()
            for line in dll_exports:
                if not start:
                    if line.strip() == start_line:
                        start = True
                    continue

                line = line.strip()
                if not line:
                    if first_empty_line_after_start_line:
                        first_empty_line_after_start_line = False
                        continue
                    else:
                        break

                parts = line.split()
                if parts[-1] != '[NONAME]':
                    mangled_symbols.append(parts[-1])
        except plumbum.CommandNotFound:
            print('dumpbin.exe not found.')

        return mangled_symbols


class Dependencies(SymbolsExporter):
    def __init__(self, tool: str):
        if tool == 'Dependencies':
            self._tool = 'Dependencies.exe'
        else:
            self._tool = tool

    def export(self, dll_path: str) -> List[str]:
        mangled_symbols = []
        export_name_pattern = parse.compile('\t Name : {0}')
        try:
            dependencies = plumbum.local[self._tool]
            dll_exports = dependencies('-exports', dll_path).splitlines()
            for line in dll_exports:
                parse_result = export_name_pattern.parse(line)
                if parse_result:
                    mangled_symbols.append(parse_result[0])
        except plumbum.CommandNotFound:
            print('"Dependencies.exe" not found.\n' \
                  'Please download it from https://github.com/lucasg/Dependencies.\n' \
                  'After installation, update your PATH environment.')

        return mangled_symbols


def create_exporter(tool: str) -> SymbolsExporter:
    if tool == 'dumpbin' or tool.endswith('dumpbin.exe'):
        return DumpBin(tool)
    elif tool == 'Dependencies' or tool.endswith('Dependencies.exe'):
        return Dependencies(tool)


def main():
    parser = argparse.ArgumentParser(fromfile_prefix_chars='@')
    parser.add_argument('-d', '--dll', required=True)
    parser.add_argument(
        '-t',
        '--tool',
        #choices=('dumpbin', 'Dependencies'),
        default='dumpbin')

    args = parser.parse_args()

    exporter = create_exporter(args.tool)
    if not exporter:
        print(f'Unexpected tool option: {args.tool}.')
        return

    mangled_symbols = exporter.export(args.dll)

    for symbol in mangled_symbols:
        try:
            print(symbol, '->',
                  cppmangle.cdecl_sym(cppmangle.demangle(symbol)))
        except:
            print(symbol)


if __name__ == '__main__':
    main()

# References:
# ../parse/dump_dll_exports.py
# https://github.com/AVGTechnologies/cppmangle
# https://github.com/r1chardj0n3s/parse
# https://github.com/PSJoshi/malware-static-analysis/blob/master/dumpbin/dumpbin.py
# https://github.com/erocarrera/pefile
# https://refactoring.guru/design-patterns/bridge/python/example
