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
    }
}
