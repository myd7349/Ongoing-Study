namespace HelloHDF5
{
    using System;
    using static System.Console;
    using System.IO;
    using System.Linq;

    using HDF.PInvoke;

    using Common;
    using HDF5.Extension;
    using static HDF5.Extension.HDF5Helper;

    using hid_t = System.Int64;

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

            WriteFile(filePath);
            ReadFile(filePath);

            TestExtent();

            ReadKey();
        }

        static void WriteFile(string filePath)
        {
            var file = File.Exists(filePath) ? 
                H5F.open(filePath, H5F.ACC_RDWR) :
                H5F.create(filePath, H5F.ACC_TRUNC);
            if (file < 0)
                throw new HDF5Exception("Failed to open or create file \"{0}\".", filePath);

            var group = GroupExists(file, "/group") ?
                H5G.open(file, "/group") :
                H5G.create(file, "/group");
            if (group < 0)
            {
                H5F.close(file);
                throw new HDF5Exception("Failed to open or create group \"{0}\".", "/group");
            }
            H5G.close(group);

            const int RANK = 2;
            const int DIM0 = 3;
            const int DIM1 = 4;

            var dataSetName = "/group/dataset";
            hid_t dataSet;
            if (DataSetExists(file, dataSetName))
                dataSet = H5D.open(file, dataSetName);
            else
                dataSet = CreateDataSet(file, dataSetName, H5T.NATIVE_INT, new ulong[RANK] { DIM0, DIM1 });

            if (dataSet < 0)
            {
                H5F.close(file);
                throw new HDF5Exception("Failed to open or create data set \"{0}\".", dataSetName);
            }

            var data = new int[DIM0, DIM1]
            {
                { 1, 2, 3, 4 },
                { 5, 6, 7, 8 },
                { 9, 10, 11, 12 }
            };
            H5D.write(dataSet, H5T.NATIVE_INT, H5S.ALL, H5S.ALL, H5P.DEFAULT, new PinnedObject(data));

            var hello = "早上好！";
            WriteAttribute(dataSet, "string", hello, true, false);
            WriteAttribute(dataSet, "string-ascii", "Hello, world!", false, false);
            WriteAttribute(dataSet, "string-vlen", hello, true, true);

            WriteAttribute(dataSet, "double", Math.PI);

            WriteEnumAttribute(dataSet, "boolean-8-bit-enum", Boolean.TRUE);

            H5D.close(dataSet);

            var chunkedDataSetName = "/group/chunked-dataset";
            var chunkedDataSet = DataSetExists(file, chunkedDataSetName) ?
                H5D.open(file, chunkedDataSetName) :
                CreateDataSet(file, chunkedDataSetName, H5T.NATIVE_INT, new ulong[] { 0, DIM1 }, new ulong[] { H5S.UNLIMITED, DIM1 }, new ulong[] { DIM0, DIM1 });
            if (chunkedDataSet < 0)
            {
                H5F.close(file);
                throw new HDF5Exception("Failed to open or create data set \"{0}\".", chunkedDataSetName);
            }

            ulong[] dims = null;
            ulong[] maxDims = null;
            GetDataSetDimensions(chunkedDataSet, ref dims, ref maxDims);
            var value = (int)dims[0];
            AppendDataSet(chunkedDataSet, H5T.NATIVE_INT, new int[DIM1] { value, value, value, value });

            H5D.close(chunkedDataSet);

            H5F.close(file);
        }

        static void ReadFile(string filePath)
        {
            var file = H5F.open(filePath, H5F.ACC_RDONLY);

            IterateObjects(file);

            var group = H5G.open(file, "group");
            IterateObjects(group);
            H5G.close(group);

            var dataSet = H5D.open(file, "/group/dataset");

            IterateObjects(dataSet);

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
#if true
            //double pi = 0.0; // Won't work
            object pi = 0.0;
            H5A.read(doubleAttribute, H5T.NATIVE_DOUBLE, new PinnedObject(pi));
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

        static void IterateObjects(hid_t hid)
        {
            WriteLine("-------------------- IterateObject --------------------");

            var objects = IterateObject(hid);
            foreach (var type in objects.Keys)
            {
                Write("{0}:", type);

                foreach (var name in objects[type])
                    Write(" {0}", name);
                WriteLine();
            }

            WriteLine("-------------------- IterateObject2 --------------------");
            var objects2 = IterateObject2(hid);
            foreach (var type in objects2.Keys)
            {
                Write("{0}:", type);

                foreach (var name in objects2[type])
                    Write(" {0}", name);
                WriteLine();
            }
        }

        static void TestExtent(hid_t file, string dataSetName, ulong[] dims, ulong[] extent)
        {
            var dataSet = CreateDataSet(file, dataSetName, H5T.NATIVE_INT,
                dims, new ulong[] { H5S.UNLIMITED, 4 }, new ulong[] { 4, 4 });

            H5D.set_extent(dataSet, extent);

            var fileSpace = H5D.get_space(dataSet);
            H5S.select_hyperslab(fileSpace, H5S.seloper_t.SET,
                new ulong[] { 0, 0 }, null, new ulong[] { 2, 4 }, null);

            var memSpace = H5S.create_simple(2, new ulong[] { 2, 4 }, null);

            if (H5D.write(dataSet, H5T.NATIVE_INT, memSpace, fileSpace, H5P.DEFAULT,
                new PinnedObject(Enumerable.Range(0, 8).ToArray())) < 0)
                WriteLine("H5D.write failed.");

            H5D.close(dataSet);
        }

        static void TestExtent()
        {
            var file = H5F.create("test-extent.h5", H5F.ACC_TRUNC);

            TestExtent(file, "1", new ulong[] { 0, 0 }, new ulong[] { 2 });

            WriteLine("--------------------------------------------------");

            TestExtent(file, "2", new ulong[] { 0, 4 }, new ulong[] { 2 });

            WriteLine("--------------------------------------------------");

            TestExtent(file, "3", new ulong[] { 0, 4 }, new ulong[] { 2, 4 });

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
