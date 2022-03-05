# coding: utf-8

import sys

import pefile

try:
    import cppmangle
    cppmangle_available = True
except ImportError:
    cppmangle_available = False


def dump_symbols(dll: str):
    pe = pefile.PE(dll)
    try:
        export_dir_data = pe.DIRECTORY_ENTRY_EXPORT
    except AttributeError:
        print('DIRECTORY_ENTRY_EXPORT not found.')
        return

    symbols = export_dir_data.symbols
    mangled_symbols = [
        symbol.name.decode('ascii') for symbol in symbols if symbol.name
    ]

    if cppmangle_available:
        demangle = lambda sym: cppmangle.cdecl_sym(cppmangle.demangle(sym))

        for symbol in mangled_symbols:
            try:
                print(symbol, '->', demangle(symbol))
            except:
                print(symbol)
    else:
        for symbol in mangled_symbols:
            print(symbol)


def main():
    if len(sys.argv) < 2:
        print('DLL path missing.')
        return

    dump_symbols(sys.argv[1])


if __name__ == '__main__':
    main()

# References:
# ../cppmangle/dump_dll_exports.py
# ../parse/dump_dll_exports.py
# https://github.com/erocarrera/pefile/blob/e3514208aa120200ca689c85a23e05f19233a503/pefile.py#L7415-L7433
