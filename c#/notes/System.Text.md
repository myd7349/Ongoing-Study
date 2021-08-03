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

