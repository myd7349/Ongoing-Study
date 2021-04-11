# coding: utf-8

import sys

import cppmangle
import plumbum


def main():
    if len(sys.argv) != 2:
        print('DLL path missing.')
        return

    dll_path = sys.argv[1]
    print('DLL path:', dll_path)

    mangled_symbols = []
    try:
        dependencies = plumbum.local['Dependencies.exe']
        dll_exports = dependencies('-exports', dll_path).splitlines()
        for line in dll_exports:
            parts = line.split()
            if len(parts) == 3 and parts[0] == 'Name':
                mangled_symbols.append(parts[2])
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
# https://github.com/AVGTechnologies/cppmangle

# Example:

# In [23]: !dump_dll_exports.py ..\Debug\NativeClassLib.dll
# DLL path: ..\Debug\NativeClassLib.dll
# ??0Person@@QAE@PBDH@Z -> public: __thiscall Person::Person(char const *,int)
# ??_FPerson@@QAEXXZ -> public: void __thiscall Person::`default constructor closure'(void)
# ?Delete@Person@@SAXPAV1@@Z -> public: static void __cdecl Person::Delete(class Person *)
# ?GetAge@Person@@QBEHXZ -> public: int __thiscall Person::GetAge(void)const
# ?GetName@Person@@QBEPBDXZ -> public: char const * __thiscall Person::GetName(void)const
# ?New@Person@@SAPAV1@PBDH@Z -> public: static class Person * __cdecl Person::New(char const *,int)
# ?Say@Person@@QBEXPBD@Z -> public: void __thiscall Person::Say(char const *)const
# ?SetAge@Person@@QAEXH@Z -> public: void __thiscall Person::SetAge(int)
# ?SetName@Person@@QAEXPBD@Z -> public: void __thiscall Person::SetName(char const *)
# GetArch

# In [24]: !dump_dll_exports.py ..\x64\Debug\NativeClassLib.dll
# DLL path: ..\x64\Debug\NativeClassLib.dll
# ??0Person@@QEAA@PEBDH@Z -> public: __cdecl Person::Person(char const *,int)
# ??_FPerson@@QEAAXXZ -> public: void __cdecl Person::`default constructor closure'(void)
# ?Delete@Person@@SAXPEAV1@@Z -> public: static void __cdecl Person::Delete(class Person *)
# ?GetAge@Person@@QEBAHXZ -> public: int __cdecl Person::GetAge(void)const
# ?GetName@Person@@QEBAPEBDXZ -> public: char const * __cdecl Person::GetName(void)const
# ?New@Person@@SAPEAV1@PEBDH@Z -> public: static class Person * __cdecl Person::New(char const *,int)
# ?Say@Person@@QEBAXPEBD@Z -> public: void __cdecl Person::Say(char const *)const
# ?SetAge@Person@@QEAAXH@Z -> public: void __cdecl Person::SetAge(int)
# ?SetName@Person@@QEAAXPEBD@Z -> public: void __cdecl Person::SetName(char const *)
# GetArch
