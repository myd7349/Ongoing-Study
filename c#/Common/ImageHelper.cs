namespace Common
{
    using System;
    // For .NET Core, install `System.Drawing.Common` at first.
    using System.Diagnostics;
    using System.Drawing;
    using System.IO;

    public static class ImageHelper
    {
        public static Image LoadFromBase64(string base64)
        {
            if (string.IsNullOrWhiteSpace(base64))
                return null;

            byte[] bytes;
            try
            {
                bytes = Convert.FromBase64String(base64);
            }
            catch (FormatException ex)
            {
                Debug.WriteLine("{0}", ex.ToString());
                return null;
            }

            using (var memoryStream = new MemoryStream(bytes))
            {
                return Image.FromStream(memoryStream);
            }
        }

        public static void OpenImage(string filePath, Action onExited = null)
        {
            string path = Environment.GetFolderPath(
                Environment.SpecialFolder.ProgramFiles);

            // create our startup process and argument
            var psi = new ProcessStartInfo(
                "rundll32.exe",
                string.Format(
                    "\"{0}{1}\", ImageView_Fullscreen {2}",
                    Environment.Is64BitOperatingSystem ?
                        path.Replace(" (x86)", "") : path,
                    @"\Windows Photo Viewer\PhotoViewer.dll",
                    filePath)
                );

            psi.UseShellExecute = false;

            var viewer = Process.Start(psi);
            if (viewer != null)
            {
                viewer.EnableRaisingEvents = true;
                viewer.Exited += (sender, args) =>
                {
                    onExited?.Invoke();
                };
            }
        }
    }
}


// References:
// [Open image in Windows Photo Viewer](https://stackoverflow.com/questions/6808029/open-image-in-windows-photo-viewer)
// [Open and close image in default image viewer](https://stackoverflow.com/questions/28661233/open-and-close-image-in-default-image-viewer)
