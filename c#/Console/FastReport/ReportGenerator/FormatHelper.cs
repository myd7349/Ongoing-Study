namespace ReportGenerator
{
    using System;
    using System.Diagnostics;
    using System.Linq;

    using FastReport.Export.Image;

    using Common;

    public static class FormatHelper
    {
        public static string ExportFormatToExtension(ExportFormat format)
        {
            switch (format)
            {
                case ExportFormat.Bmp: return ".bmp";
                case ExportFormat.Gif: return ".gif";
                case ExportFormat.Jpeg: return ".jpg";
                case ExportFormat.Metafile: return ".emf";
                case ExportFormat.Png: return ".png";
                case ExportFormat.Tiff: return ".tiff";
                case ExportFormat.Pdf: return ".pdf";
            }

            return "";
        }

        public static ExportFormat ExportFormatFromExtension(string extension)
        {
            if (extension == null)
                throw new ArgumentNullException("extension");

            extension = extension.ToLower();

            switch (extension)
            {
                case ".bmp":
                case ".dib":
                    return ExportFormat.Bmp;
                case ".gif":
                    return ExportFormat.Gif;
                case ".jpg":
                case ".jpeg":
                    return ExportFormat.Jpeg;
                case ".emf":
                case ".wmf":
                    return ExportFormat.Metafile;
                case ".png":
                    return ExportFormat.Png;
                case ".tiff":
                case ".tif":
                    return ExportFormat.Tiff;
                case ".pdf":
                    return ExportFormat.Pdf;
                default:
                    return ExportFormat.Invalid;
            }
        }

        public static ImageExportFormat ExportFormatToImageExportFormat(ExportFormat format)
        {
            Debug.Assert(!EnumHelper.HasDuplicateValues<ExportFormat>());

            switch (format)
            {
                case ExportFormat.Invalid:
                case ExportFormat.Pdf:
                    throw new NotImplementedException(format.ToString());
                default:
                    return (ImageExportFormat)(int)format;
            }
        }

        public static ExportFormat ImageExportFormatToExportFormat(ImageExportFormat format)
        {
            Debug.Assert(!EnumHelper.HasDuplicateValues<ExportFormat>());

            return (ExportFormat)(int)format;
        }
    }
}
