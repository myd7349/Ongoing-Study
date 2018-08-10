# encoding: utf-8

import codecs
import functools
import os
import os.path
import shutil
import subprocess


code_template = \
'''{0}

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <io.h>
#include <tchar.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

int _tmain()
{{
    {1}

    _tprintf(_T("测试。\\n"));
    _tprintf(_T("%s\\n"), gai_strerror(WSAGetLastError()));

#ifdef _DEBUG
    _tsystem(_T("pause"));
#endif
    
    return 0;
}}
'''


class CodeGenerator:
    def __init__(self, encoding, func_name, locale):
        self._encoding = encoding
        self._func_name = func_name
        self._locale = locale
        
    @property
    def encoding(self):
        return self._encoding
    
    @property
    def func_name(self):
        return self._func_name
    
    @property
    def locale(self):
        return self._locale
    
    @property
    def code_file_title(self):
        return '_'.join((attr for _, attr in self.__dict__.items() if attr))
                
    @property
    def code_file_name(self):
        return self.code_file_title + '.cpp'
                
    def generate_header(self):
        raise NotImplementedError('generate_header should be implemented by subclass')
    
    def generate_func_call(self):
        raise NotImplementedError('generate_header should be implemented by subclass')
    
    def generate(self):
        return code_template.format(
            self.generate_header(),
            self.generate_func_call())
    

class UnicodeCodeGenerator(CodeGenerator):
    def __init__(self, encoding, func_name, locale):
        super().__init__(encoding, func_name, locale)
        
    def generate_header(self):
        return '#define _UNICODE\n#define UNICODE'


setlocale_funcs = ('setlocale', '_tsetlocale')


class SetLocaleGenerator(UnicodeCodeGenerator):
    def __init__(self, encoding, func_name):
        assert func_name in setlocale_funcs
        super().__init__(encoding, func_name, '')
        
    # Note:
    # setlocale(LC_COLLATE, "");
    # will not work.
    def generate_func_call(self):
        if self.func_name == 'setlocale':
            return 'setlocale(LC_ALL, "");'
        else:
            return '_tsetlocale(LC_ALL, _T(""));'


setmode_locales = ('_O_U8TEXT', '_O_U16TEXT', '_O_WTEXT')


class SetModeGenerator(UnicodeCodeGenerator):
    def __init__(self, encoding, locale):
        assert locale in setmode_locales
        super().__init__(encoding, '_setmode', locale)
        
    def generate_func_call(self):
        return '_setmode(_fileno(stdout), {0});'.format(self.locale)
    

if __name__ == '__main__':
    encodings = (
        'utf_8',
        #'utf_8_sig',  # Not work, don't know why.
        'utf_16_le',
        'utf_16_be'
    )
    boms = {
        'utf_8': b'',
        'utf_8_sig': codecs.BOM_UTF8,
        'utf_16_le': codecs.BOM_UTF16_LE,
        'utf_16_be': codecs.BOM_UTF16_BE,
    }
    
    partial_generators = (
        functools.partial(SetLocaleGenerator, func_name='setlocale'),
        functools.partial(SetLocaleGenerator, func_name='_tsetlocale'),
        functools.partial(SetModeGenerator, locale='_O_U8TEXT'),
        functools.partial(SetModeGenerator, locale='_O_U16TEXT'),
        functools.partial(SetModeGenerator, locale='_O_WTEXT'),
        )

    current_dir = os.path.dirname(__file__)
    target_dir = os.path.join(current_dir, 'build')
    if not os.path.exists(target_dir):
        os.mkdir(target_dir)

    shutil.copy(os.path.join(current_dir, 'CMakeSettings.json'),
        os.path.join(target_dir, 'CMakeSettings.json'))
    
    cmakelists_file_path = os.path.join(target_dir, r'CMakeLists.txt')
    print('Creating CMakeLists file: {0} ...'.format(cmakelists_file_path))
    with open(cmakelists_file_path, mode='w', encoding='utf_8_sig') as cmakelists:
        for encoding in encodings:
            for generator in partial_generators:
                g = generator(encoding=encoding)

                code_file_path = os.path.join(target_dir, g.code_file_name)
                print('Creating code file: {0} ...'.format(code_file_path))
                with open(code_file_path, mode='wb') as code_file:
                    code_file.write(boms[encoding])
                    code = g.generate().replace('\n', os.linesep).encode(encoding)
                    code_file.write(code)
                
                cmake_command = 'add_executable ({0} "{1}")\n'.format(
                    g.code_file_title, g.code_file_name)
                cmakelists.write(cmake_command)

    os.chdir(target_dir)
    subprocess.run(['cmake', '.'])
    subprocess.run('cmake --build . --config Release')

    release_dir = os.path.join(target_dir, 'Release')
    for exe in os.listdir(release_dir):
        if exe.endswith('.exe'):
            print('{0} Run {1} {0}'.format('-' * ((79 - len(exe) - 6) // 2), exe))
            subprocess.run(os.path.join(release_dir, exe))


# References:
# Python 3.6.4 Documentation/7.2.3. Standard Encodings
# https://stackoverflow.com/questions/25150955/python-iterating-through-object-attributes
# https://stackoverflow.com/questions/18239373/python-writing-a-ucs-2-little-endian-utf-16-le-file-with-bom
# https://stackoverflow.com/questions/22459020/python-decode-utf-16-file-with-bom
# https://stackoverflow.com/questions/2492077/output-unicode-strings-in-windows-console-app
# https://www.codeproject.com/articles/34068/unicode-output-to-the-windows-console
# https://stackoverflow.com/questions/2849010/output-unicode-to-console-using-c-in-windows
# http://www.cppblog.com/fdsajhg/archive/2010/09/03/125764.aspx
