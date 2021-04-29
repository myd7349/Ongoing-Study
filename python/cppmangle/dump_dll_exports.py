# coding: utf-8

import sys

import cppmangle
import parse
import plumbum


def main():
    if len(sys.argv) != 2:
        print('DLL path missing.')
        return

    dll_path = sys.argv[1]
    print('DLL path:', dll_path)
    
    export_name_pattern = parse.compile('\t Name : {0}')

    mangled_symbols = []
    try:
        dependencies = plumbum.local['Dependencies.exe']
        dll_exports = dependencies('-exports', dll_path).splitlines()
        for line in dll_exports:
            parse_result = export_name_pattern.parse(line)
            if parse_result:
                mangled_symbols.append(parse_result[0])
    except plumbum.CommandNotFound:
        print('"Dependencies.exe" not found.\n' \
              'Please download it from https://github.com/lucasg/Dependencies.\n' \
              'After installation, update your PATH environment.')
        return

    for symbol in mangled_symbols:
        try:
            print(symbol, '->', cppmangle.cdecl_sym(cppmangle.demangle(symbol)))
        except:
            print(symbol)

if __name__ == '__main__':
    main()


# References:
# ../parse/dump_dll_exports.py
# https://github.com/AVGTechnologies/cppmangle
# https://github.com/r1chardj0n3s/parse
