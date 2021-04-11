namespace HDF5.Extension.UnitTests
{
    using System.IO;
    using System.Reflection;

    using HDF.PInvoke;
    using NUnit.Framework;

    using static HDF5.Extension.HDF5Helper;

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
        public void TestFixedLengthStringAttribute()
        {
            var str = "Hello, world!";
            Assert.IsTrue(WriteStringAttribute(file_, "ascii", str, false, false));
            Assert.IsTrue(ReadStringAttribute(file_, "ascii") == str);

            Assert.IsTrue(WriteStringAttribute(file_, "ascii", str + str, false, false));
            Assert.IsTrue(ReadStringAttribute(file_, "ascii") == str);

            str = "早上好！";
            Assert.IsTrue(WriteStringAttribute(file_, "utf8", str, true, false));
            Assert.IsTrue(ReadStringAttribute(file_, "utf8") == str);

            Assert.IsTrue(WriteStringAttribute(file_, "utf8", str + str, true, false));
            Assert.IsTrue(ReadStringAttribute(file_, "utf8") == str);
        }

        [Test]
        public void TestVariableStringAttribute()
        {
            var str = "Hello, world!";
            Assert.IsTrue(WriteStringAttribute(file_, "ascii-vlen", str, false, true));
            Assert.IsTrue(ReadStringAttribute(file_, "ascii-vlen") == str);

            Assert.IsTrue(WriteStringAttribute(file_, "ascii-vlen", str + str));
            Assert.IsTrue(ReadStringAttribute(file_, "ascii-vlen") == str + str);

            str = "早上好！";
            Assert.IsTrue(WriteStringAttribute(file_, "utf8-vlen", str, true, true));
            Assert.IsTrue(ReadStringAttribute(file_, "utf8-vlen") == str);

            Assert.IsTrue(WriteStringAttribute(file_, "utf8-vlen", str + str));
            Assert.IsTrue(ReadStringAttribute(file_, "utf8-vlen") == str + str);
        }
    }
}


// References:
// https://docs.nunit.org/articles/nunit/writing-tests/setup-teardown/index.html
// [NUnit: SetUp and TearDown for each test in a test fixture across multiple Fixtures](NUnit: SetUp and TearDown for each test in a test fixture across multiple Fixtures)
// [SetUp and TearDown for all fixtures in namespace](https://github.com/nunit/nunit/issues/3140)
