namespace HelloHDF5DotNet
{
    using static System.Console;
    using System.Text;

    using HDF5DotNet;

    class Program
    {
        static void Main(string[] args)
        {
            var filePath = args.Length >= 1 ? args[0] : "./a.h5";

            try
            {
                WriteFile(filePath);
                ReadFile(filePath);
            }
            catch (HDFException ex)
            {
                WriteLine("H5::Exception: {0}\n{1}", ex.Message, ex.StackTrace);
            }
            finally
            {
                ReadKey();
            }
        }

        private static void WriteFile(string filePath)
        {
            var file = H5F.create(filePath, H5F.CreateMode.ACC_TRUNC);

            var group = H5G.create(file, "/group");
            H5G.close(group);

            const int RANK = 2;
            const int DIM0 = 3;
            const int DIM1 = 4;
            var dims = new long[RANK] { DIM0, DIM1 };
            var dataSpace = H5S.create_simple(RANK, dims);

            var dataSet = H5D.create(file, "/group/dataset", H5T.H5Type.NATIVE_INT, dataSpace);
            H5S.close(dataSpace);

            var data = new int[DIM0,DIM1]
            {
                { 1, 2, 3, 4 },
                { 5, 6, 7, 8 },
                { 9, 10, 11, 12 }
            };
            H5D.write(dataSet, new H5DataTypeId(H5T.H5Type.NATIVE_INT), new H5Array<int>(data));

            var dataType = new H5DataTypeId(H5T.H5Type.NATIVE_INT);
            dataSpace = H5S.create(H5S.H5SClass.SCALAR);
            var integerAttribute = H5A.create(dataSet, "int", dataType, dataSpace);
            H5A.write(integerAttribute, dataType, new H5Array<int>(new int[1] { 42 }));
            H5A.close(integerAttribute);
            H5S.close(dataSpace);
            //H5T.close(dataType); // Read-only.

            var str = "Hello, world!";
            var strBytes = Encoding.ASCII.GetBytes(str);
            // There is a H5T.get_cset, but there does not seem to be a way of setting the character encoding, i.e. set_cset.
            dataType = H5T.copy(H5T.H5Type.C_S1);
            H5T.setSize(dataType, strBytes.Length);
            dataSpace = H5S.create(H5S.H5SClass.SCALAR);
            var stringAttribute = H5A.create(dataSet, "string", dataType, dataSpace);
            H5A.write(stringAttribute, dataType, new H5Array<byte>(strBytes));
            H5A.close(stringAttribute);
            H5S.close(dataSpace);
            H5T.close(dataType);

            H5D.close(dataSet);

            H5F.close(file);
        }

        private static void ReadFile(string filePath)
        {
            var file = H5F.open(filePath, H5F.OpenMode.ACC_RDONLY);

            var dataSet = H5D.open(file, "/group/dataset");

            var fileSpace = H5D.getSpace(dataSet);

            var rank = H5S.getSimpleExtentNDims(fileSpace);
            WriteLine("Rank: {0}", rank);

            var dims = H5S.getSimpleExtentDims(fileSpace);
            Write("Dims:");
            foreach (var d in dims)
                Write(" {0}", d);
            WriteLine();

            H5S.close(fileSpace);

            var ints = new int[1];
            var intAttribute = H5A.openName(dataSet, "int");
            H5A.read(intAttribute, H5A.getType(intAttribute), new H5Array<int>(ints));
            WriteLine("int: {0}", ints[0]);
            H5A.close(intAttribute);

            var stringAttribute = H5A.openName(dataSet, "string");
            var stringType = H5A.getType(stringAttribute);
            var stringSize = H5T.getSize(stringType);
            WriteLine("string length: {0}", stringSize);
            var buffer = new byte[stringSize];
            H5A.read(stringAttribute, stringType, new H5Array<byte>(buffer));
            WriteLine("string: {0}", Encoding.ASCII.GetString(buffer));
            H5T.close(stringType);
            H5A.close(stringAttribute);

            if (rank == 2)
            {
                var data = new int[dims[0], dims[1]];
                H5D.read(dataSet, H5D.getType(dataSet), new H5Array<int>(data));

                for (int i = 0; i < data.GetLength(0); ++i)
                {
                    for (int j = 0; j < data.GetLength(1); ++j)
                        Write(" {0}", data[i, j]);

                    WriteLine();
                }
            }

            H5D.close(dataSet);

            H5F.close(file);
        }
    }
}

// References:
// http://hdf5.net/
// [HDF5 Example code](https://stackoverflow.com/questions/7939723/hdf5-example-code)
// [Using UTF-8 Encoding in HDF5 Applications](https://support.hdfgroup.org/HDF5/doc/Advanced/UsingUnicode/index.html)
// [HDF5DotNet and string in compound data type](http://hdf-forum.184993.n3.nabble.com/HDF5DotNet-and-string-in-compound-data-type-td4027979.html)
// [C# hdf5 文件操作入门](https://www.bilibili.com/read/cv5836507/)
// https://github.com/hypesystem/HDF5Reader
