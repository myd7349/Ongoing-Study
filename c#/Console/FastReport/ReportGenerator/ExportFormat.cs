namespace ReportGenerator
{
    using FastReport.Export.Image;

    public enum ExportFormat
    {
        Invalid = -1,
        Bmp = ImageExportFormat.Bmp,
        Png = ImageExportFormat.Png,
        Jpeg = ImageExportFormat.Jpeg,
        Gif = ImageExportFormat.Gif,
        Tiff = ImageExportFormat.Tiff,
        Metafile = ImageExportFormat.Metafile,
        Pdf = 6,
    }
}


// References:
// [Enum "Inheritance"](https://stackoverflow.com/questions/757684/enum-inheritance)
