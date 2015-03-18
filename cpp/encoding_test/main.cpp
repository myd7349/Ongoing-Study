// 2014-06-25T20:34+08:00
// UTF-8 with BOM
//#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <iostream>
//#include <iterator>
#include <locale>
#include <stdexcept>
#include <string>

//#define _UNICODE
#undef _UNICODE

#include <tchar.h>

#ifdef _UNICODE
# define _tcout std::wcout
# define _tstring std::wstring
#else
# define _tcout std::cout
# define _tstring std::string
#endif

typedef unsigned char byte;

#include "GB2312.h"
#include "UTF8_without_BOM.h"
#include "UTF8_with_BOM.h"

#ifdef _MSC_VER
# include "UTF16_BE.h"
# include "UTF16_LE.h"
#endif

/*
In python:
>>> '海阔天空'.encode('utf-16')
b'\xff\xfewm\x14\x96)Yzz'
>>> '海阔天空'.encode('utf-16-le')
b'wm\x14\x96)Yzz'
>>> '海阔天空'.encode('utf-16-be')
b'mw\x96\x14Y)zz'
>>> chr(0x7a)
'z'
>>> chr(0x59)
'Y'

Output of this program: (Unicode mode)
GB2312: 海阔天空
77 6d 14 96 29 59 7a 7a
UTF-8 without BOM: 娴烽様澶╃┖
34 5a fd 70 d8 69 b6 6f 43 25 16 25
UTF-8 with BOM: 海阔天空
77 6d 14 96 29 59 7a 7a
UTF-16 BE: 海阔天空
77 6d 14 96 29 59 7a 7a
UTF-16 LE: 海阔天空
77 6d 14 96 29 59 7a 7a

So, windows uses UTF-16-LE to represent a string in UNICODE mode.
In non-unicode mode, cp936 is used.
*/
void dump(const _tstring &str)
{
    std::size_t wpos = str.rfind(_T(' '));
    if (_tstring::npos == wpos)
    {
        return;
    }

    const byte *beg = reinterpret_cast<const byte *>(str.c_str() + wpos + 1);
    const byte *end = reinterpret_cast<const byte *>(str.c_str() + str.size());

#if 0
    _tcout << std::hex;
    std::ostream_iterator<byte, _TCHAR> oit(_tcout, _T(" ")); // Caution
    std::copy(beg, end, oit);
    _tcout << std::dec << std::endl;
#else
    _tcout << std::setfill(_T('0')) << std::hex;
    for (const byte *p = beg; p != end; ++p)
    {
        if (*p <= 0x7f && std::isprint(static_cast<char>(*p)))
        {
            _tcout << static_cast<char>(*p);
        }
        else
        {
            // In non-unicode mode, if we want to print the value of '*p'
            // in hexadecimal format, we have to cast it into an integer.
            _tcout << _T("\\x") << std::setw(2) << static_cast<int>(*p);
        }
    }
    _tcout << std::setfill(_T(' ')) << std::dec << std::endl;
#endif
}

int _tmain()
{
#ifdef _UNICODE
    try {
        std::locale::global(std::locale(""));
    } catch (const std::runtime_error &exc) {
        std::cout << exc.what() << std::endl;
    }
#endif

    _tcout << STR_GB2312 << std::endl;
    dump(STR_GB2312);

    // In Python 3.4.1:
    /*
    >>> str_utf8 = '海阔天空'.encode('utf-8')
    >>> str_utf8
    b'\xe6\xb5\xb7\xe9\x98\x94\xe5\xa4\xa9\xe7\xa9\xba'
    >>> str_utf8.decode('gb2312')
    Traceback (most recent call last):
    File "<pyshell#9>", line 1, in <module>
    str_utf8.decode('gb2312')
    UnicodeDecodeError: 'gb2312' codec can't decode byte 0x98 in position 4: illegal multibyte sequence
    >>> str_utf8.decode('gb18030')
    '娴烽様澶╃┖'
    >>> str_utf8.decode('cp936')
    '娴烽様澶╃┖'
    */
    _tcout << STR_UTF8_WITHOUT_BOM << std::endl;
    dump(STR_UTF8_WITHOUT_BOM);

    _tcout << STR_UTF8_WITH_BOM << std::endl;
    dump(STR_UTF8_WITH_BOM);

#ifdef _MSC_VER
    _tcout << STR_UTF16_BE << std::endl;
    dump(STR_UTF16_BE);
    _tcout << STR_UTF16_LE << std::endl;
    dump(STR_UTF16_LE);
#endif

#ifdef _MSC_VER
    _tsystem(_T("pause"));
#endif
    return 0;
}
