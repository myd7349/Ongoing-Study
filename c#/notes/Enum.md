[Enum ToString with user friendly strings](https://stackoverflow.com/questions/479410/enum-tostring-with-user-friendly-strings)

[String representation of an Enum](https://stackoverflow.com/questions/424366/string-representation-of-an-enum)

[C# non-boxing conversion of generic enum to int?](https://stackoverflow.com/questions/1189144/c-sharp-non-boxing-conversion-of-generic-enum-to-int)

[Enum "Inheritance"](https://stackoverflow.com/questions/757684/enum-inheritance)

> - All enums must derive from `System.Enum`
> - Because of the above, all enums are value types and hence sealed

and what I want do:

> ```csharp
> namespace FastReport.Export.Image
> {
>     public enum ImageExportFormat
>     {
>         Bmp = 0,
>         Png = 1,
>         Jpeg = 2,
>         Gif = 3,
>         Tiff = 4,
>         Metafile = 5,
>     }
> }
> 
> using FastReport.Export.Image;
> 
> public enum ExportFormat : ImageExportFormat
> {
>        Pdf = 6,
> }
> ```

[How to prevent duplicate values in enum?](https://stackoverflow.com/questions/1425777/how-to-prevent-duplicate-values-in-enum)

[Enums.NET](https://github.com/TylerBrinkley/Enums.NET)
