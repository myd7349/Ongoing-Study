namespace Common
{
    using System;
    // For .NET Core, install `System.Drawing.Common` at first.
    using System.Drawing;
    using System.IO;

    public static class ImageHelper
    {
        public static Image LoadFromBase64(string base64)
        {
            if (string.IsNullOrWhiteSpace(base64))
                return null;

            var bytes = Convert.FromBase64String(base64);
            using (var memoryStream = new MemoryStream(bytes))
            {
                return Image.FromStream(memoryStream);
            }
        }
    }
}
