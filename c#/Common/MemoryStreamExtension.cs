namespace Common
{
    using System;
    using System.IO;
    using System.Text;

    public static class MemoryStreamExtension
    {
        public static string ReadAllText(this MemoryStream memoryStream, Encoding encoding = null)
        {
            if (memoryStream == null)
                throw new ArgumentNullException("memoryStream");

            using (var streamReader = encoding == null ? new StreamReader(memoryStream) : new StreamReader(memoryStream, encoding))
                return streamReader.ReadToEnd();
        }
    }
}


// References:
// [How do you get a string from a MemoryStream?](https://stackoverflow.com/questions/78181/how-do-you-get-a-string-from-a-memorystream)
