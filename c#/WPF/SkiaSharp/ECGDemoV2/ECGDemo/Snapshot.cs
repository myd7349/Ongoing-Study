using System;

using Microsoft.Win32;

using SkiaSharp;

namespace ECGDemo
{
    public static class Snapshot
    {
        public static string GetSaveFileName()
        {
            var filters = new[]
            {
                "Bitmap Files|*.bmp;*.dib",
                "JPEG Files|*.jpg;*.jpeg",
                "PNG Files|*.png",
            };

            var saveFileDialog = new SaveFileDialog();
            saveFileDialog.FileName = $"Snapshot_{DateTime.Now:yyyy-MM-dd_HH-mm-ss.fff}";
            saveFileDialog.OverwritePrompt = true;
            saveFileDialog.Filter = string.Join("|", filters);
            saveFileDialog.FilterIndex = 3; // 1-based

            if (saveFileDialog.ShowDialog() == true)
                return saveFileDialog.FileName;

            return null;
        }

        public static SKEncodedImageFormat GetImageFormat(string fileExtension)
        {
            if (string.IsNullOrEmpty(fileExtension))
                throw new ArgumentException("Invalid file extension");

            if (fileExtension[0] != '.')
                fileExtension = "." + fileExtension;

            switch (fileExtension.ToLower())
            {
                case ".bmp":
                case ".dib": return SKEncodedImageFormat.Bmp;
                case ".gif": return SKEncodedImageFormat.Gif;
                case ".jpg":
                case ".jpeg": return SKEncodedImageFormat.Jpeg;
                case ".png": return SKEncodedImageFormat.Png;
                default: throw new NotImplementedException();
            }
        }
    }
}
