namespace HDF5.Extension.UnitTests
{
    using System;
    using System.IO;
    using System.Reflection;

    using HDF.PInvoke;
    using NUnit.Framework;

    using static HDF5.Extension.HDF5Helper;

    enum Boolean : byte
    {
        False,
        True,
    }

    enum MyEnumI64 : long
    {
        Foo = long.MinValue,
        Zero = 0,
        Bar = long.MaxValue,
    }

    enum MyEnumU64 : ulong
    {
        Foo = ulong.MinValue,
        Zero = 0,
        Bar = ulong.MaxValue,
    }

    [TestFixture]
    public class HDF5HelperUnitTests
    {
#if false
        // This will get:
        // "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\Common7\\IDE\\test.h5"
        private readonly string TestFileName = Path.GetFullPath("./test.h5");
#elif false
        // H5F.create will return -1 in SetUp.
        private readonly string TestFileName = "./test.h5";
#else
        private readonly string TestFileName = Path.Combine(
            Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location),
            "test.h5");
#endif
        private long file_;

        [OneTimeSetUp]
        protected void SetUp()
        {
            file_ = H5F.create(TestFileName, H5F.ACC_TRUNC);
            Assert.IsTrue(file_ > 0);
        }

        [OneTimeTearDown]
        protected void TearDown()
        {
            Assert.IsTrue(H5F.close(file_) >= 0);
        }

        [Test]
        public void TestDataSetCreation()
        {
            var group1 = H5G.create(file_, "group1");
            Assert.IsTrue(group1 >= 0);

            var dataSet1 = CreateDataSet(group1, "dataset1", H5T.NATIVE_INT, new ulong[] { 1 });
            Assert.IsTrue(dataSet1 >= 0);
            H5D.close(dataSet1);

            H5G.close(group1);
            var dataSet2 = CreateDataSet(file_, "group1/dataset2", H5T.NATIVE_INT, new ulong[] { 100 }, new ulong[] { H5S.UNLIMITED }, new ulong[] { 10 });
            Assert.IsTrue(dataSet2 >= 0);
            H5D.close(dataSet2);

            Assert.That(
                () => CreateDataSet(file_, "group2/dataset3", H5T.NATIVE_INT, new ulong[] { 1 }),
                Throws.InstanceOf<HDF5Exception>());
            Assert.IsFalse(GroupExists(file_, "group2"));
        }

        [Test]
        public void TestFixedLengthStringAttribute()
        {
            var str = "Hello, world!";
            Assert.IsTrue(WriteAttribute(file_, "ascii", str, false, false));
            Assert.IsTrue(ReadStringAttribute(file_, "ascii") == str);

            Assert.IsTrue(WriteAttribute(file_, "ascii", str + str, false, false));
            Assert.IsTrue(ReadStringAttribute(file_, "ascii") == str);

            str = "早上好！";
            Assert.IsTrue(WriteAttribute(file_, "utf8", str, true, false));
            Assert.IsTrue(ReadStringAttribute(file_, "utf8") == str);

            Assert.IsTrue(WriteAttribute(file_, "utf8", str + str, true, false));
            Assert.IsTrue(ReadStringAttribute(file_, "utf8") == str);
        }

        [Test]
        public void TestVariableStringAttribute()
        {
            var str = "Hello, world!";
            Assert.IsTrue(WriteAttribute(file_, "ascii-vlen", str, false, true));
            Assert.IsTrue(ReadStringAttribute(file_, "ascii-vlen") == str);

            Assert.IsTrue(WriteAttribute(file_, "ascii-vlen", str + str));
            Assert.IsTrue(ReadStringAttribute(file_, "ascii-vlen") == str + str);

            str = "早上好！";
            Assert.IsTrue(WriteAttribute(file_, "utf8-vlen", str, true, true));
            Assert.IsTrue(ReadStringAttribute(file_, "utf8-vlen") == str);

            Assert.IsTrue(WriteAttribute(file_, "utf8-vlen", str + str));
            Assert.IsTrue(ReadStringAttribute(file_, "utf8-vlen") == str + str);
        }

        [Test]
        public void TestCreateEnumType()
        {
            var type = CreateEnumType(new string[] { "FALSE", "TRUE" }, new int[] { 0, 1 });
            Assert.IsFalse(type < 0);
            H5T.close(type);

            var type2 = CreateEnumType(new string[] { "FALSE", "TRUE" }, new Boolean[] { Boolean.False, Boolean.True });
            Assert.IsFalse(type2 < 0);
            H5T.close(type2);
        }

        [Test]
        public void Test8bitEnum()
        {
            Assert.IsTrue(WriteEnumAttribute(file_, "boolean-8-bit-enum", Boolean.False));
            Assert.IsTrue(ReadEnumAttribute<Boolean>(file_, "boolean-8-bit-enum") == Boolean.False);
            Assert.IsTrue(WriteEnumAttribute(file_, "boolean-8-bit-enum", Boolean.True));
            Assert.IsTrue(ReadEnumAttribute<Boolean>(file_, "boolean-8-bit-enum") == Boolean.True);
        }

        [Test]
        public void TestMyEnumI64()
        {
            Assert.IsTrue(WriteEnumAttribute(file_, "myenum-i64", MyEnumI64.Bar));
            Assert.IsTrue(ReadEnumAttribute<MyEnumI64>(file_, "myenum-i64") == MyEnumI64.Bar);
            Assert.IsTrue(WriteEnumAttribute(file_, "myenum-i64", MyEnumI64.Foo));
            Assert.IsTrue(ReadEnumAttribute<MyEnumI64>(file_, "myenum-i64") == MyEnumI64.Foo);
            Assert.IsTrue(WriteEnumAttribute(file_, "myenum-i64", MyEnumI64.Zero));
            Assert.IsTrue(ReadEnumAttribute<MyEnumI64>(file_, "myenum-i64") == MyEnumI64.Zero);
        }

        [Test]
        public void TestMyEnumU64()
        {
            Assert.IsTrue(MyEnumU64.Foo == MyEnumU64.Zero);
            Assert.IsTrue(WriteEnumAttribute(file_, "myenum-u64", MyEnumU64.Bar));
            Assert.IsTrue(ReadEnumAttribute<MyEnumU64>(file_, "myenum-u64") == MyEnumU64.Bar);
            Assert.IsTrue(WriteEnumAttribute(file_, "myenum-u64", MyEnumU64.Foo));
            Assert.IsTrue(ReadEnumAttribute<MyEnumU64>(file_, "myenum-u64") == MyEnumU64.Foo);
            Assert.IsTrue(WriteEnumAttribute(file_, "myenum-u64", MyEnumU64.Zero));
            Assert.IsTrue(ReadEnumAttribute<MyEnumU64>(file_, "myenum-u64") == MyEnumU64.Zero);
        }

        [Test]
        public void TestBooleanAttribute()
        {
            Assert.IsTrue(WriteAttribute(file_, "true", true));
            Assert.IsTrue(WriteAttribute(file_, "false", false));
        }

        [Test]
        public void TestNumericAttribute()
        {
            Assert.IsTrue(WriteAttribute(file_, "i8", sbyte.MaxValue));
            Assert.IsTrue(ReadScalarNumericAttribute<sbyte>(file_, "i8") == sbyte.MaxValue);
            Assert.IsTrue(ReadScalarNumericAttribute<int>(file_, "i8") == sbyte.MaxValue);

            Assert.IsTrue(WriteAttribute(file_, "u8", byte.MaxValue));
            Assert.IsTrue(ReadScalarNumericAttribute<byte>(file_, "u8") == byte.MaxValue);
            Assert.IsTrue(ReadScalarNumericAttribute<int>(file_, "u8") == byte.MaxValue);

            // Very funny!
            Assert.IsTrue(WriteScalarNumericAttribute(file_, "u8", 0xAA, H5T.NATIVE_INT8));
            Assert.IsFalse(ReadScalarNumericAttribute<byte>(file_, "u8") == 0xAA);
            Assert.IsTrue(ReadScalarNumericAttribute<byte>(file_, "u8") == 0);
            Assert.IsTrue(WriteScalarNumericAttribute(file_, "u8", 0xAA, H5T.NATIVE_UINT8));
            Assert.IsTrue(ReadScalarNumericAttribute<byte>(file_, "u8") == 0xAA);

            Assert.IsTrue(WriteAttribute(file_, "i16", short.MaxValue));
            Assert.IsTrue(ReadScalarNumericAttribute<short>(file_, "i16") == short.MaxValue);
            Assert.IsTrue(ReadScalarNumericAttribute<int>(file_, "i16") == short.MaxValue);

            Assert.IsTrue(WriteAttribute(file_, "u16", ushort.MaxValue));
            Assert.IsTrue(ReadScalarNumericAttribute<ushort>(file_, "u16") == ushort.MaxValue);
            Assert.IsTrue(ReadScalarNumericAttribute<int>(file_, "u16") == ushort.MaxValue);

            Assert.IsTrue(WriteAttribute(file_, "i32", int.MaxValue));
            Assert.IsTrue(ReadScalarNumericAttribute<int>(file_, "i32") == int.MaxValue);
            Assert.IsTrue(ReadScalarNumericAttribute<long>(file_, "i32") == int.MaxValue);

            Assert.IsTrue(WriteAttribute(file_, "u32", uint.MaxValue));
            Assert.IsTrue(ReadScalarNumericAttribute<uint>(file_, "u32") == uint.MaxValue);
            Assert.IsTrue(ReadScalarNumericAttribute<long>(file_, "u32") == uint.MaxValue);

            Assert.IsTrue(WriteAttribute(file_, "i64", long.MaxValue));
            Assert.IsTrue(ReadScalarNumericAttribute<long>(file_, "i64") == long.MaxValue);

            Assert.IsTrue(WriteAttribute(file_, "u64", ulong.MaxValue));
            Assert.IsTrue(ReadScalarNumericAttribute<ulong>(file_, "u64") == ulong.MaxValue);

            Assert.IsTrue(WriteAttribute(file_, "float", float.MaxValue));
            Assert.IsTrue(WriteAttribute(file_, "double", double.MaxValue));
            Assert.IsTrue(WriteAttribute(file_, "pi", Math.PI));

            Assert.IsTrue(WriteAttribute(file_, "i8", Math.PI));
            Assert.IsTrue(ReadScalarNumericAttribute<sbyte>(file_, "i8") == 3);
            Assert.IsTrue(ReadScalarNumericAttribute<int>(file_, "i8") == 3);
        }
    }
}


// References:
// https://docs.nunit.org/articles/nunit/writing-tests/setup-teardown/index.html
// [NUnit: SetUp and TearDown for each test in a test fixture across multiple Fixtures](NUnit: SetUp and TearDown for each test in a test fixture across multiple Fixtures)
// [SetUp and TearDown for all fixtures in namespace](https://github.com/nunit/nunit/issues/3140)
