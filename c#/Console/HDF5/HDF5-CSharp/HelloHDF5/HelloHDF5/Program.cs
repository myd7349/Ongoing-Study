namespace HelloHDF5
{
    using static System.Console;
    using System.IO;

    using HDF.PInvoke;
    using HDF5CSharp;

    class Program
    {
        static void Main(string[] args)
        {
            var filePath = args.Length >= 1 ? args[0] : "./a.h5";

            if (!File.Exists(filePath))
                WriteFile(filePath);

            if (File.Exists(filePath))
                ReadFile(filePath);
        }

        static void WriteFile(string filePath)
        {
            var file = Hdf5.CreateFile(filePath);

            var group = Hdf5.CreateOrOpenGroup(file, "group");

            Hdf5.WriteDataset(group, "dataset",
                new int[,]
                {
                    { 1, 2, 3, 4 },
                    { 5, 6, 7, 8 },
                    { 9, 10, 11, 12 }
                });

            var hello = "早上好！";
            Hdf5.WriteStringAttribute(group, "string", hello, "dataset");

            Hdf5.CloseGroup(group);
            Hdf5.CloseFile(file);
        }

        static void ReadFile(string filePath)
        {
            var file = Hdf5.OpenFile(filePath, true);
            var group = Hdf5.CreateOrOpenGroup(file, "group");

            var (ok, rawData) = Hdf5.ReadDataset<int>(group, "dataset");
            if (ok)
            {
                var data = (int[,])rawData;
                for (int i = 0; i < data.GetLength(0); ++i)
                {
                    for (int j = 0; j < data.GetLength(1); ++j)
                        Write($"{data[i, j],3}");
                    WriteLine();
                }
            }

            //var dataSet = H5D.open(group, "dataset");
            //var hello = Hdf5.ReadUnicodeString(dataSet, "string");
            //H5D.close(dataSet);
            //WriteLine($"string: {hello}");

            Hdf5.CloseGroup(group);
            Hdf5.CloseFile(file);
        }
    }
}
