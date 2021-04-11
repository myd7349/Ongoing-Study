// Note:
// The OO APIs looks good. But I just can not run this program successfully.
// References:
// [Build as Any CPU](https://github.com/sharpHDF/sharpHDF/issues/4)
// [it seems the project is not maintained anymore](https://github.com/sharpHDF/sharpHDF/issues/8)
namespace HelloSharpHDF
{
    using static System.Console;
    using System.Diagnostics;
    using System.IO;
    using System.Linq;

    using sharpHDF.Library.Enums;
    using sharpHDF.Library.Objects;

    class Program
    {
        static void Main(string[] args)
        {
            var filePath = args.Length >= 1 ? args[0] : "./a.h5";

            if (!File.Exists(filePath))
                WriteFile(filePath);

            if (File.Exists(filePath))
                ReadFile(filePath);

            ReadKey();
        }

        static void WriteFile(string filePath)
        {
            var file = Hdf5File.Create(filePath);

            var group = file.Groups.Add("group");

            const int DIM0 = 3;
            const int DIM1 = 4;

            var data = new int[DIM0, DIM1]
            {
                { 1, 2, 3, 4 },
                { 5, 6, 7, 8 },
                { 9, 10, 11, 12 }
            };

            var dims = new Hdf5DimensionProperty[]
            {
                new Hdf5DimensionProperty
                {
                    CurrentSize = DIM0,
                },
                new Hdf5DimensionProperty
                {
                    CurrentSize = DIM1,
                }
            };
            var dataSet = group.Datasets.Add(
                "dataset",
                Hdf5DataTypes.Int32,
                dims.ToList());
            dataSet.SetData(data);

            file.Close();
        }

        static void ReadFile(string filePath)
        {
            using (var file = new Hdf5File(filePath))
            {
                var dataSet = file.Groups["group"].Datasets["dataset"];
                if (dataSet.Dataspace.NumberOfDimensions == 2 &&
                    dataSet.DataType.Type == Hdf5DataTypes.Int32)
                {
                    var dims = dataSet.Dataspace.DimensionProperties
                        .Select(dp => dp.CurrentSize).ToArray();
                    Debug.Assert(dims.Length == 2);

                    WriteLine("Size: {0}x{1}", dims[0], dims[1]);
                    var data = (int[,])dataSet.GetData();

                    for (int i = 0; i < data.GetLength(0); ++i)
                    {
                        for (int j = 0; j < data.GetLength(1); ++j)
                            Write($"{data[i, j],3}");
                        WriteLine();
                    }
                }
            }
        }
    }
}
