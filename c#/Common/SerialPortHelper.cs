namespace Common
{
    using System.Diagnostics;
    using System.IO.Ports;

    public static class SerialPortHelper
    {
        public static int ReadBytes(this SerialPort serialPort, byte[] buffer, int offset, int count)
        {
            Debug.Assert(serialPort != null && serialPort.IsOpen);
            Debug.Assert(buffer != null);
            Debug.Assert(offset >= 0 && count > 0 && offset + count <= buffer.Length);

            int bytesRead = 0;

            while (bytesRead != count)
            {
                //Debug.WriteLine("offset, count, bytesRead: {0}, {1}, {2}",
                //    offset, count, bytesRead);
                int bytesReadThisTime = serialPort.Read(buffer, offset, count - bytesRead);
                bytesRead += bytesReadThisTime;
                offset += bytesReadThisTime;
            }

            return count;
        }
    }
}

// References:
// [SerialPort.Read always returns one byte or character](https://social.msdn.microsoft.com/Forums/vstudio/en-US/91041b37-f6be-44ab-8f5c-7c0986f74aa8/serialportread-always-returns-one-byte-or-character)
