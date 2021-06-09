namespace FlushFileTest
{
    using System;
    using System.IO;
    using System.Linq;
    using System.Threading;

    using HDF.PInvoke;
    using hid_t = System.Int64;

    using NLog;

    using Common;
    using Common.IO;
    using static HDF5.Extension.HDF5Helper;
    using System.Runtime.InteropServices;

    class Program
    {
        private static DateTime now_ = DateTime.Now;
        private static string nowString_ = now_.ToString("o");
        private static Logger logger_ = NLogAdapter.CreateCustomLogger(nowString_, logFileLayout: "{0}.log");
        private static int isRunning_ = 0;
        private static int flushFile_ = 0;

        private static void WriteToFile()
        {
            var filePath = Path.Combine(IOHelper.GetAppPath(), nowString_.Replace(':', '-') + ".h5");

            var file = H5F.create(filePath, H5F.ACC_TRUNC);
            if (file < 0)
            {
                logger_.Error("Failed to create HDF5 file \"{0}\"", filePath);
                return;
            }

            hid_t dataSet;
            try
            {
                dataSet = CreateDataSet(file, "data", H5T.NATIVE_INT,
                    new ulong[] { 0 }, new ulong[] { H5S.UNLIMITED }, new ulong[] { 256 });
            }
            catch (Exception ex)
            {
                H5F.close(file);
                logger_.Error(ex, "Failed to create data set.");
                return;
            }

            FlushFile(file);

            var random = new Random();

            int count = 0;

            while (Thread.VolatileRead(ref isRunning_) > 0)
            {
                var numbers = Enumerable.Range(count, random.Next(1, 100)).ToArray();

                // Extend data set
                var newDimensions = new ulong[] { (ulong)(count + numbers.Length) };
                if (H5D.set_extent(dataSet, newDimensions) < 0)
                {
                    logger_.Error("Failed to extend data set.");
                    break;
                }

                // Append data
                AppendData(dataSet, numbers, ref count);

                logger_.Info("Write {0}...{1} to file successfully!", numbers.Min(), numbers.Max());

                if (Thread.VolatileRead(ref flushFile_) > 0)
                {
                    FlushFile(file);
                    Thread.VolatileWrite(ref flushFile_, 0);

                    logger_.Info("Flush file.");
                }

                Thread.Sleep(1);
            }

            H5D.close(dataSet);
            H5F.close(file);

            logger_.Info("Done!");
        }

        private static void AppendData<T>(hid_t dataSet, T[] data, ref int rows)
        {
            var fileSpace = H5D.get_space(dataSet);
            if (fileSpace < 0)
                throw new Exception("Failed to get data space of data set.");

            var offset = new ulong[] { (ulong)rows };
            var count = new ulong[] { (ulong)data.Length };

            if (H5S.select_hyperslab(fileSpace, H5S.seloper_t.SET, offset, null, count, null) < 0)
                throw new Exception("H5S.select_hyperslab failed.");

            var memSpace = H5S.create_simple(1, count, null);
            if (memSpace < 0)
                throw new Exception("H5S.create_simple failed.");

            if (H5D.write(dataSet, NumericTypeToHDF5Type<T>(), memSpace, fileSpace, H5P.DEFAULT, new PinnedObject(data)) < 0)
                throw new Exception("H5D.write failed.");

            H5S.close(memSpace);
            H5S.close(fileSpace);

            rows += data.Length;
        }

        static void Main(string[] args)
        {
            isRunning_ = 1;

            var thread = new Thread(WriteToFile);
            thread.Start();

            //while (Console.KeyAvailable)
            //while (Win32Interop._kbhit() != 0)
            while (true)
            {
                Console.Write("'f' for Flush, 'q' for Quit, and 't' for Terminate> ");
                var command = Console.ReadLine().ToLower();
                if (string.IsNullOrWhiteSpace(command))
                    continue;
                
                switch (command[0])
                {
                    case 'f':
                        Thread.VolatileWrite(ref flushFile_, 1);
                        break;
                    case 'q':
                        Thread.VolatileWrite(ref isRunning_, 0);
                        thread.Join();
                        return;
                    case 't':
                        thread.Abort(); // Danger!
                        thread.Join();
                        return;
                    default:
                        break;
                }
            }
        }
    }

    public static class Win32Interop
    {
        [DllImport("crtdll.dll")]
        public static extern int _kbhit();
    }
}


// References:
// [Corrupt files when creating HDF5 files without closing them (h5py)](https://stackoverflow.com/questions/31287744/corrupt-files-when-creating-hdf5-files-without-closing-them-h5py)
// [_getch, kbhit](http://forum.codecall.net/topic/67098-getch-kbhit/)
// [Aborting Threads](http://www.albahari.com/threading/part4.aspx#_Aborting_Threads)
// [How to kill a thread instantly in C#?](https://stackoverflow.com/questions/1327102/how-to-kill-a-thread-instantly-in-c)
// [C# kbhit() equivalent](https://www.gamedev.net/forums/topic/179669-c-kbhit-equivalent/)
