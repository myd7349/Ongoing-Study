[Convert UTF-8 to Chinese Simplified (GB2312)](https://stackoverflow.com/questions/2855842/convert-utf-8-to-chinese-simplified-gb2312)

> ```csharp
> public string GB2312ToUtf8(string gb2312String)
> {
>     Encoding fromEncoding = Encoding.GetEncoding("gb2312");
>     Encoding toEncoding = Encoding.UTF8;
>     return EncodingConvert(gb2312String, fromEncoding, toEncoding);
> }
> 
> public string Utf8ToGB2312(string utf8String)
> {
>     Encoding fromEncoding = Encoding.UTF8;
>     Encoding toEncoding = Encoding.GetEncoding("gb2312");
>     return EncodingConvert(utf8String, fromEncoding, toEncoding);
> }
> 
> public string EncodingConvert(string fromString, Encoding fromEncoding, Encoding toEncoding)
> {            
>     byte[] fromBytes = fromEncoding.GetBytes(fromString);
>     byte[] toBytes = Encoding.Convert(fromEncoding, toEncoding, fromBytes);
> 
>     string toString = toEncoding.GetString(toBytes);
>     return toString;
> }
> ```

[How to read an ANSI encoded file containing special characters](https://stackoverflow.com/questions/1432064/how-to-read-an-ansi-encoded-file-containing-special-characters)

[C#: Converting String to Sbyte*](https://stackoverflow.com/questions/5666073/c-converting-string-to-sbyte)

[Fastest way to convert a possibly-null-terminated ascii byte[] to a string?](https://stackoverflow.com/questions/144176/fastest-way-to-convert-a-possibly-null-terminated-ascii-byte-to-a-string)

[Converting string to byte array in C#](https://stackoverflow.com/questions/16072709/converting-string-to-byte-array-in-c-sharp)

[CodePagesEncodingProvider](https://docs.microsoft.com/en-us/dotnet/api/system.text.codepagesencodingprovider?view=net-6.0)

> ISO-8859-1 (code page 28591).
