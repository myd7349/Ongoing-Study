[Why does .net use the UTF16 encoding for string, but uses UTF-8 as default for saving files?](https://stackoverflow.com/questions/14942092/why-does-net-use-the-utf16-encoding-for-string-but-uses-utf-8-as-default-for-s)

> [From here](http://csharpindepth.com/Articles/General/strings.aspx)
>
> > Essentially, string uses the UTF-16 character encoding form
>
> But when saving vs [StreamWriter](http://msdn.microsoft.com/en-us/library/wtbhzte9.aspx) :
>
> > This constructor creates a StreamWriter with UTF-8 encoding without a Byte-Order Mark (BOM),

[Character encoding in .NET](https://docs.microsoft.com/en-us/dotnet/standard/base-types/character-encoding-introduction)

> 16-bit Unicode Transformation Format ([UTF-16](https://www.unicode.org/faq/utf_bom.html#UTF16)) is a character encoding system that uses 16-bit *code units* to represent Unicode code points. .NET uses UTF-16 to encode the text in a `string`. A `char` instance represents a 16-bit code unit.
