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

[.NET Format a string with fixed spaces](https://stackoverflow.com/questions/644017/net-format-a-string-with-fixed-spaces)

```csharp
string s = "String goes here";
string lineAlignedRight  = String.Format("{0,27}", s);
string lineAlignedCenter = String.Format("{0,-27}",
    String.Format("{0," + ((27 + s.Length) / 2).ToString() +  "}", s));
string lineAlignedLeft   = String.Format("{0,-27}", s);
```

[C# convert int to string with padding zeros?](https://stackoverflow.com/questions/4325267/c-sharp-convert-int-to-string-with-padding-zeros)

```csharp
i.ToString().PadLeft(4, '0'); // okay, but doesn't work for negative numbers
i.ToString("0000"); // explicit form
i.ToString("D4"); // short form format specifier
$"{i:0000}"; // string interpolation (C# 6.0+)
```

[Pad left with zeroes](https://stackoverflow.com/questions/11901395/pad-left-with-zeroes)

[How to do Alignment within string.Format in C#?](https://stackoverflow.com/questions/4579506/how-to-do-alignment-within-string-format-in-c)

https://www.csharp-examples.net/align-string-with-spaces/
