[c/notes/unicode.md](../../c/notes/unicode.md)

[ThePHD](https://github.com/ThePhD) has an article: [Any Encoding, Ever - ztd.text and Unicode for C++](https://thephd.dev/any-encoding-ever-ztd-text-unicode-cpp).

https://github.com/soasis/text

https://github.com/tzlaine/text

https://github.com/tahonermann/text_view

https://github.com/libogonek/ogonek

[Effective way to find any file's Encoding](https://stackoverflow.com/questions/3825390/effective-way-to-find-any-files-encoding)

> ```csharp
> /// <summary>
> /// Determines a text file's encoding by analyzing its byte order mark (BOM).
> /// Defaults to ASCII when detection of the text file's endianness fails.
> /// </summary>
> /// <param name="filename">The text file to analyze.</param>
> /// <returns>The detected encoding.</returns>
> public static Encoding GetEncoding(string filename)
> {
>     // Read the BOM
>     var bom = new byte[4];
>     using (var file = new FileStream(filename, FileMode.Open, FileAccess.Read))
>     {
>         file.Read(bom, 0, 4);
>     }
> 
>     // Analyze the BOM
>     if (bom[0] == 0x2b && bom[1] == 0x2f && bom[2] == 0x76) return Encoding.UTF7;
>     if (bom[0] == 0xef && bom[1] == 0xbb && bom[2] == 0xbf) return Encoding.UTF8;
>     if (bom[0] == 0xff && bom[1] == 0xfe && bom[2] == 0 && bom[3] == 0) return Encoding.UTF32; //UTF-32LE
>     if (bom[0] == 0xff && bom[1] == 0xfe) return Encoding.Unicode; //UTF-16LE
>     if (bom[0] == 0xfe && bom[1] == 0xff) return Encoding.BigEndianUnicode; //UTF-16BE
>     if (bom[0] == 0 && bom[1] == 0 && bom[2] == 0xfe && bom[3] == 0xff) return new UTF32Encoding(true, true);  //UTF-32BE
> 
>     // We actually have no idea what the encoding is if we reach this point, so
>     // you may wish to return null instead of defaulting to ASCII
>     return Encoding.ASCII;
> }
> ```

https://github.com/sheredom/utf8.h

[breakpad/convert_UTF.cc](https://github.com/google/breakpad/blob/main/src/common/convert_UTF.cc)

[GitHub - haipome/utf8: A simple utf8 decode/encode lib in c](https://github.com/haipome/utf8)

[llvm/ConvertUTF.h at master · llvm-mirror/llvm · GitHub](https://github.com/llvm-mirror/llvm/blob/master/include/llvm/Support/ConvertUTF.h)

https://github.com/frang75/nappgui_src/blob/main/src/sewer/unicode.c

[readunicode](https://github.com/kiwirafe/readunicode)

[GitHub - woboq/utf8sse4: Convert from UTF-8 to UTF-16 using SSE4](https://github.com/woboq/utf8sse4)

[GitHub - boostorg/nowide: Boost.Nowide - Standard library functions with UTF-8 API on Windows](https://github.com/boostorg/nowide)

TortoiseGit\src\Utils\UnicodeUtils.h

[为什么 mysql 要额外加入一个 utf8mb4 数据类型，而不是原地升级 utf8？](https://www.zhihu.com/question/347040967/answer/832021621)

> 早期的[RFC2279](https://link.zhihu.com/?target=https%3A//www.ietf.org/rfc/rfc2279.txt)规定一个UTF8字符被编码为1～6个byte。后来才改成了1～4个。
> 
> 在Unicode中，3个Byte可以支持所有的BMP（basic multi-lingual plane）的字符；但是无法支持SMP（supplementary multi-lingual plane），包括emoji（这是重灾区），一些生僻的[CJK字符](https://www.zhihu.com/search?q=CJK字符&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"answer"%2C"sourceId"%3A832021621})，一部分生僻的符号等。对于主要的文字（英文、欧洲各种语种、中文、日文……），3个byte的utf8也算是够用。
> 
> UTF8早期的标准[RFC2279](https://link.zhihu.com/?target=https%3A//www.ietf.org/rfc/rfc2279.txt)规定一个UTF8字符是1～6个Byte。这也是为什么早期Mysql把一个UTF8字符设计为6个Byte的原因。但是2003年11月，出了新的标准[RFC3629](https://link.zhihu.com/?target=https%3A//tools.ietf.org/html/rfc3629)，规定一个UTF8字符是1～4个Byte。

[libaribcaption/utf_helper.hpp at master · xqq/libaribcaption · GitHub](https://github.com/xqq/libaribcaption/blob/master/src/base/utf_helper.hpp)

[libaribcaption/wchar_helper.hpp at master · xqq/libaribcaption · GitHub](https://github.com/xqq/libaribcaption/blob/master/src/base/wchar_helper.hpp)

[simdutf](https://github.com/simdutf/simdutf)

[uncrustify/unicode.h at master · uncrustify/uncrustify · GitHub](https://github.com/uncrustify/uncrustify/blob/master/src/unicode.h)

[nppexec/SysUniConv.h at master · d0vgan/nppexec · GitHub](https://github.com/d0vgan/nppexec/blob/master/NppExec/src/encodings/SysUniConv.h)

[How to print UTF-8 strings to std::cout on Windows?](https://stackoverflow.com/questions/45575863/how-to-print-utf-8-strings-to-stdcout-on-windows)

[Change default code page of Windows console to UTF-8](https://superuser.com/questions/269818/change-default-code-page-of-windows-console-to-utf-8)

https://discuss.python.org/t/pep-597-enable-utf-8-mode-by-default-on-windows/3122

https://superuser.com/questions/239810/setting-utf8-as-default-character-encoding-in-windows-7

https://superuser.com/questions/1033088/is-it-possible-to-set-locale-of-a-windows-application-to-utf-8

[Unicode in Microsoft Windows - Wikipedia](https://en.wikipedia.org/wiki/Unicode_in_Microsoft_Windows#UTF-8)

> Microsoft Windows has a code page designated for [UTF-8](https://en.wikipedia.org/wiki/UTF-8 "UTF-8"), code page 65001.[[9]](https://en.wikipedia.org/wiki/Unicode_in_Microsoft_Windows#cite_note-9) Prior to Windows 10 insider build 17035 (November 2017),[[10]](https://en.wikipedia.org/wiki/Unicode_in_Microsoft_Windows#cite_note-10) it was impossible to set the locale code page to 65001, leaving this 
> code page only available for (a) explicit conversion functions such as 
> MultiByteToWideChar and/or (b) the [Win32 console](https://en.wikipedia.org/wiki/Win32_console "Win32 console") command `chcp 65001` to translate stdin/out between UTF-8 and UTF-16. This means that "narrow" functions, in particular [fopen](https://en.wikipedia.org/wiki/C_file_input/output#fopen "C file input/output") (which opens files), cannot be called with UTF-8 strings, and in fact there is no way to open all possible files using `fopen` no matter what the locale is set to and/or what bytes are put in the 
> string, as none of the available locales can produce all possible UTF-16
>  characters. This problem also applies to all other APIs that take or 
> return 8 bit strings, including Windows ones such as `SetWindowText`.
> 
> On all modern non-Windows platforms, the file-name string passed to `fopen` is effectively UTF-8. This produces an incompatibility between other 
> platforms and Windows. The normal work-around is to add Windows-specific
>  code to convert UTF-8 to UTF-16 using [MultiByteToWideChar](https://en.wikipedia.org/wiki/MultiByteToWideChar "MultiByteToWideChar") and call the "wide" function instead of `fopen`.[[11]](https://en.wikipedia.org/wiki/Unicode_in_Microsoft_Windows#cite_note-11) Another popular work-around is to convert the name to the [8.3 filename](https://en.wikipedia.org/wiki/8.3_filename "8.3 filename") equivalent, this is necessary if the `fopen` is inside a library function that takes a string filename and thus 
> calling another function is not possible. There were also proposals to 
> add new APIs to portable libraries such as [Boost](https://en.wikipedia.org/wiki/Boost_(C%2B%2B_libraries) "Boost (C++ libraries)") to do the necessary conversion, by adding new functions for opening and
>  renaming files. These functions would pass filenames through unchanged 
> on Unix, but translate them to UTF-16 on Windows. Such a library, 
> Boost.Nowide,[[12]](https://en.wikipedia.org/wiki/Unicode_in_Microsoft_Windows#cite_note-12) was accepted into Boost[[13]](https://en.wikipedia.org/wiki/Unicode_in_Microsoft_Windows#cite_note-13) and will be part of the 1.73 release.[*[needs update](https://en.wikipedia.org/wiki/Wikipedia:Manual_of_Style/Dates_and_numbers#Chronological_items "Wikipedia:Manual of Style/Dates and numbers")*] This would allow code to be "portable", but required just as many code changes as calling the wide functions.
> 
> In April 2018, with insider build 17035 (nominal build 17134) for
>  Windows 10, a "Beta: Use Unicode UTF-8 for worldwide language support" 
> checkbox appeared for setting the locale code page to UTF-8.[[a]](https://en.wikipedia.org/wiki/Unicode_in_Microsoft_Windows#cite_note-14) This allows for calling "narrow" functions, including `fopen` and `SetWindowTextA`, with UTF-8 strings. In May 2019 Microsoft added the ability for a program to set the code page to UTF-8 itself.[[14]](https://en.wikipedia.org/wiki/Unicode_in_Microsoft_Windows#cite_note-Microsoft-UTF-8-15)

[c++ - Character Set Encoding of Visual Studio - Stack Overflow](https://stackoverflow.com/questions/56587568/character-set-encoding-of-visual-studio)

[String and character literals (C++) | Microsoft Docs](https://docs.microsoft.com/en-us/cpp/cpp/string-and-character-literals-cpp?view=msvc-170&viewFallbackFrom=vs-2019#encoding)

[Difference between char* and wchar_t*](https://stackoverflow.com/questions/19532785/difference-between-char-and-wchar-t)

> On Windows, APIs that take `char *` use the current code page whereas `wchar_t *` APIs use UTF-16. As a result, you should **always** use `wchar_t` on Windows.

[char, wchar_t, char8_t, char16_t, char32_t | Microsoft Docs](https://docs.microsoft.com/en-us/cpp/cpp/char-wchar-t-char16-t-char32-t?view=msvc-170)

> The **`char`** type was the original character type in C and C++. The **`char`** type can be used to store characters from the ASCII character set or 
> any of the ISO-8859 character sets, and individual bytes of multi-byte 
> characters such as Shift-JIS or the UTF-8 encoding of the Unicode 
> character set. In the Microsoft compiler, **`char`** is an 8-bit type. It's a distinct type from both **`signed char`** and **`unsigned char`**. By default, variables of type **`char`** get promoted to **`int`** as if from type **`signed char`** unless the [`/J`](https://docs.microsoft.com/en-us/cpp/build/reference/j-default-char-type-is-unsigned?view=msvc-170) compiler option is used. Under **`/J`**, they're treated as type **`unsigned char`** and get promoted to **`int`** without sign extension.
> 
> The **`wchar_t`** type is an 
> implementation-defined wide character type. In the Microsoft compiler, 
> it represents a 16-bit wide character used to store Unicode encoded as 
> UTF-16LE, the native character type on Windows operating systems. The 
> wide character versions of the Universal C Runtime (UCRT) library 
> functions use **`wchar_t`** and its pointer and array types as parameters and return values, as do the wide character versions of the native Windows API.

wcwidth

- [wcwidth](https://pypi.org/project/wcwidth/)

- [widecharwidth](https://github.com/ridiculousfish/widecharwidth)
