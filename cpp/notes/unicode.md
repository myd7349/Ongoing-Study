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
