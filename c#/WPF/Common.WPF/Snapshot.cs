using System;
using System.Diagnostics;
using System.IO;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;

using Microsoft.Win32;

using Common.WPF.Imaging;
using static Common.WPF.Imaging.ImageHelper;

namespace Common.WPF
{
    public static class Snapshot
    {
        public static RenderTargetBitmap TakeSnapshot(this Visual visual)
        {
            Rect bounds = VisualTreeHelper.GetDescendantBounds(visual);
            double dpi = 96d;

            var renderTargetBitmap = new RenderTargetBitmap(
                (int)bounds.Width, (int)bounds.Height, dpi, dpi,
                PixelFormats.Default);

            var drawingVisual = new DrawingVisual();
            using (DrawingContext dc = drawingVisual.RenderOpen())
            {
                VisualBrush visualBrush = new VisualBrush(visual);
                dc.DrawRectangle(visualBrush, null, new Rect(new Point(), bounds.Size));
            }

            renderTargetBitmap.Render(drawingVisual);

            return renderTargetBitmap;
        }

        public static BitmapEncoder TakeSnapshot(this Visual visual, ImageFormat format)
        {
            var bitmap = visual.TakeSnapshot();
            var bitmapEncoder = CreateBitmapEncoder(format);
            bitmapEncoder.Frames.Add(BitmapFrame.Create(bitmap));
            return bitmapEncoder;
        }

        public static void TakeSnapshot(this Visual visual, ImageFormat format, Stream stream)
        {
            var bitmapEncoder = visual.TakeSnapshot(format);
            bitmapEncoder.Save(stream);
        }

        public static void TakeSnapshot(this Visual visual, string filePath)
        {
            var fileExtension = Path.GetExtension(filePath);
            var format = GetImageFormat(fileExtension);
            using (var stream = File.Create(filePath))
                visual.TakeSnapshot(format, stream);
        }

        public static void Save(this RenderTargetBitmap bitmap, ImageFormat format, Stream stream)
        {
            var bitmapEncoder = CreateBitmapEncoder(format);
            bitmapEncoder.Frames.Add(BitmapFrame.Create(bitmap));
            bitmapEncoder.Save(stream);
        }

        public static void Save(this RenderTargetBitmap bitmap, string filePath)
        {
            var fileExtension = Path.GetExtension(filePath);
            var format = GetImageFormat(fileExtension);
            using (var stream = File.Create(filePath))
                bitmap.Save(format, stream);
        }

        public static string GetSaveFileName()
        {
            var filters = new[]
            {
                "Bitmap Files|*.bmp;*.dib",
                "JPEG Files|*.jpg;*.jpeg",
                "PNG Files|*.png",
                "TIFF Files|*.tif;*.tiff",
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

        public static void EasyTakeSnapshot(this Visual visual)
        {
            var filePath = GetSaveFileName();
            if (filePath != null)
                visual.TakeSnapshot(filePath);
        }

        public static void EasySaveBitmap(BitmapSource bitmap)
        {
            var filePath = GetSaveFileName();
            if (filePath == null)
                return;

            var fileExtension = Path.GetExtension(filePath);
            var format = GetImageFormat(fileExtension);
            var bitmapEncoder = CreateBitmapEncoder(format);
            bitmapEncoder.Frames.Add(BitmapFrame.Create(bitmap));
            using (var stream = File.Create(filePath))
                bitmapEncoder.Save(stream);
        }

        public static void LaunchSnippingTool()
        {
            var snippingToolPath = Environment.Is64BitProcess ?
                @"C:\Windows\System32\SnippingTool.exe" :
                @"C:\Windows\Sysnative\SnippingTool.exe";

            if (!File.Exists(snippingToolPath)) // Fix for Win11
                snippingToolPath = "SnippingTool";

            var snippingToolProcess = new Process();
            snippingToolProcess.EnableRaisingEvents = true;
            snippingToolProcess.StartInfo.FileName = snippingToolPath;
            snippingToolProcess.Start();
        }
    }
}


// References:
// [Saving a canvas to png C# wpf](https://stackoverflow.com/questions/21411878/saving-a-canvas-to-png-c-sharp-wpf)
// [WPF中的Canvas存为Bitmap](https://chowdera.com/2022/01/202201060408527374.html)
// [How to open a common dialog box (WPF .NET)](https://docs.microsoft.com/en-us/dotnet/desktop/wpf/windows/how-to-open-common-system-dialog-box?view=netdesktop-6.0)
// [how to filter more than once in Microsoft.Win32.OpenFileDialog()](https://stackoverflow.com/questions/10493417/how-to-filter-more-than-once-in-microsoft-win32-openfiledialog)
// https://github.com/wieslawsoltes/Core2D/blob/master/src/Core2D.Screenshot/Capture.cs
// [How do I correctly transform an image in WPF?](https://stackoverflow.com/questions/34219949/how-do-i-correctly-transform-an-image-in-wpf)
// [Saving image (screenshot) of control in WPF - MVVM Pattern](https://stackoverflow.com/questions/65611709/saving-image-screenshot-of-control-in-wpf-mvvm-pattern)
// [Add a button on my winform to run the Snipping Tool application](https://stackoverflow.com/questions/28318284/add-a-button-on-my-winform-to-run-the-snipping-tool-application)
