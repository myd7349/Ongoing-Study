namespace HelloHDF5
{
    using System;
    using static System.Console;
    using System.IO;

    using HDF.PInvoke;

    using Common;
    using static HDF5.Extension.HDF5Helper;

    enum Boolean : byte
    {
        FALSE = 0,
        TRUE = 1
    }

    class Program
    {
        static void Main(string[] args)
        {
            var filePath = args.Length >= 1 ? args[0] : "./a.h5";

#if !DEBUG
            if (!File.Exists(filePath))
#endif
                WriteFile(filePath);

            if (File.Exists(filePath))
                ReadFile(filePath);

            ReadKey();
        }

        static void WriteFile(string filePath)
        {
            var file = H5F.create(filePath, H5F.ACC_TRUNC);

            var group = H5G.create(file, "/group");
            H5G.close(group);

            const int RANK = 2;
            const int DIM0 = 3;
            const int DIM1 = 4;
            var dims = new ulong[RANK] { DIM0, DIM1 };
            var dataSpace = H5S.create_simple(RANK, dims, null);

            var dataSet = H5D.create(file, "/group/dataset", H5T.NATIVE_INT, dataSpace);
            H5S.close(dataSpace);

            var data = new int[DIM0, DIM1]
            {
                { 1, 2, 3, 4 },
                { 5, 6, 7, 8 },
                { 9, 10, 11, 12 }
            };
            H5D.write(dataSet, H5T.NATIVE_INT, H5S.ALL, H5S.ALL, H5P.DEFAULT, new PinnedObject(data));

            var hello = "早上好！";
            WriteStringAttribute(dataSet, "string", hello, true, false);
            WriteStringAttribute(dataSet, "string-ascii", "Hello, world!", false, false);
            WriteStringAttribute(dataSet, "string-vlen", hello, true, true);

            dataSpace = H5S.create(H5S.class_t.SCALAR);
            var doubleAttribute = H5A.create(dataSet, "double", H5T.NATIVE_DOUBLE, dataSpace);
            H5S.close(dataSpace);
            H5A.write(doubleAttribute, H5T.NATIVE_DOUBLE, new PinnedObject(new double[] { Math.PI }));
            H5A.close(doubleAttribute);

            WriteEnumAttribute(dataSet, "boolean-8-bit-enum", Boolean.TRUE);

            H5D.close(dataSet);
            H5F.close(file);
        }

        static void ReadFile(string filePath)
        {
            var file = H5F.open(filePath, H5F.ACC_RDONLY);

            var dataSet = H5D.open(file, "/group/dataset");

            var dataSpace = H5D.get_space(dataSet);

            var rank = H5S.get_simple_extent_ndims(dataSpace);
            if (rank == 2)
            {
                var dims = new ulong[2];
                H5S.get_simple_extent_dims(dataSpace, dims, null);

                var data = new int[dims[0], dims[1]];
                H5D.read(dataSet, H5T.NATIVE_INT, H5S.ALL, H5S.ALL, H5P.DEFAULT, new PinnedObject(data));

                for (int i = 0; i < data.GetLength(0); ++i)
                {
                    for (int j = 0; j < data.GetLength(1); ++j)
                        Write($"{data[i,j],3}");
                    WriteLine();
                }
            }

            H5S.close(dataSpace);

            var doubleAttribute = H5A.open(dataSet, "double");
#if false
            double pi = 0.0;
            var handle = GCHandle.Alloc(pi, GCHandleType.Pinned);
            H5A.read(doubleAttribute, H5T.NATIVE_DOUBLE, handle.AddrOfPinnedObject());
            handle.Free();
            WriteLine($"PI = {pi}");
#else
            var values = new double[1];
            H5A.read(doubleAttribute, H5T.NATIVE_DOUBLE, new PinnedObject(values));
            WriteLine($"PI = {values[0]}");
#endif
            H5A.close(doubleAttribute);

            WriteLine($"string: {ReadStringAttribute(dataSet, "string")}");
            WriteLine($"string-ascii: {ReadStringAttribute(dataSet, "string-ascii")}");
            WriteLine($"string-vlen: {ReadStringAttribute(dataSet, "string-vlen")}");
            WriteLine($"boolean-8-bit-enum: {ReadEnumAttribute<Boolean>(dataSet, "boolean-8-bit-enum")}");

            H5D.close(dataSet);
            H5F.close(file);
        }
    }
}

// References:
// https://github.com/HDFGroup/HDF.PInvoke/blob/master/UnitTests/H5DTest/H5Dwrite.cs
// https://github.com/HDFGroup/HDF.PInvoke/blob/master/UnitTests/H5DTest/H5Dfill.cs
// https://github.com/HDFGroup/HDF.PInvoke/blob/master/UnitTests/H5ATest/H5ATest.cs
// https://github.com/HDFGroup/HDF.PInvoke/blob/master/UnitTests/H5ATest/H5Awrite.cs
// https://github.com/HDFGroup/HDF.PInvoke/blob/master/UnitTests/H5ATest/H5Aget_name.cs
// [C/C++ HDF5 Read string attribute](https://stackoverflow.com/questions/31344648/c-c-hdf5-read-string-attribute)

