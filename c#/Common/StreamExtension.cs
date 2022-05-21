using System.IO;

namespace Common.IO
{
    public static class StreamExtension
    {
        public static long Seek(this Stream stream, long offset)
        {
            return stream.Seek(offset, SeekOrigin.Begin);
        }
    }
}
