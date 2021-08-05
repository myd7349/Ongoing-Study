namespace INIUnitTests
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Linq;

    using FluentAssertions;
    using NUnit.Framework;

    using Common;


    [TestFixture]
    public class IniFileUnitTests
    {
        [OneTimeSetUp]
        protected void SetUp()
        {
            temporaryIniFilePath_ = Path.GetTempFileName();
            ini_ = new IniFile(temporaryIniFilePath_);
        }

        [OneTimeTearDown]
        protected void TearDown()
        {
            File.Delete(temporaryIniFilePath_);
        }

        [Test]
        public void Test()
        {
            // Path.GetTempFileName will create a uniquely named, zero-byte temporary file
            // on disk and returns the full path of that file.
            File.Exists(temporaryIniFilePath_).Should().BeTrue();
            new FileInfo(temporaryIniFilePath_).Length.Should().Be(0);

            ini_.GetSections().Should().BeEmpty();
            ini_.GetKeys("bang").Should().BeEmpty();

            var serverSection = new KeyValuePair<string, string>[]
                {
                    new KeyValuePair<string, string>("IP", "127.0.0.1"),
                    new KeyValuePair<string, string>("Port", "8080"),
                };
            ini_.WriteSection("Server", serverSection);
            File.Exists(temporaryIniFilePath_).Should().BeTrue();
            new FileInfo(temporaryIniFilePath_).Length.Should().NotBe(0);

            var sections = ini_.GetSections();
            sections.Length.Should().Be(1);
            sections.Should().Equal("Server");

            ini_.HasSection("Server").Should().BeTrue();
            ini_.HasSection("server").Should().BeTrue();

            ini_.ReadSection("serVer").Should().Equal(serverSection);

            var serverKeys = serverSection.Select(kv => kv.Key).ToArray();
            ini_.GetKeys("SERVER").Should().Equal("IP", "Port");

            ini_.HasKey("server", "ip").Should().BeTrue();
            ini_.ReadString("server", "ip").Should().Equals("127.0.0.1");
            ini_.ReadString("server", "port").Should().Equals("8080");
            ini_.ReadInt("server", "port").Should().Be(8080);
            ini_.ReadUInt("server", "port").Should().Be(8080);

            ini_.Write("server", "ip", "192.168.0.1").Should().BeTrue();
            ini_.ReadString("server", "ip").Should().Equals("192.168.0.1");
            ini_.Write("server", "port", 80).Should().BeTrue();
            ini_.ReadInt("server", "port").Should().Be(80);

            ini_.ReadString("server", "ip-not-existed", null).Should().BeEmpty();
            ini_.ReadString("server", "ip-not-existed", "ghost").Should().Be("ghost");
            ini_.ReadInt("server", "port-not-existed").Should().Be(0);
            ini_.ReadInt("server", "port-not-existed", 3000).Should().Be(3000);

            ini_.Write("server", "UseIPv6", false).Should().BeTrue();
            ini_.ReadBoolean("server", "useipv6").Should().BeFalse();
            ini_.Write("server", "UseIPv6", true).Should().BeTrue();
            ini_.ReadString("server", "UseIPv6").Should().Be("true");
            ini_.ReadBoolean("server", "UseIPv6").Should().BeTrue();
            ini_.Read("server", "UseIPv6", false, bool.TryParse).Should().BeTrue();
            ini_.Write("server", "UseIPv6", "no").Should().BeTrue();
            ini_.Read("server", "UseIPv6", false, bool.TryParse).Should().BeFalse();

            ini_.Write("Session", "User", "Jerry").Should().BeTrue();
            ini_.Write("Session", "Password", "admin").Should().BeTrue();
            ini_.GetSections().Should().Equal("Server", "Session");

            var lastSeen = DateTime.Now;
            ini_.Write("Session", "LastSeen", DateTime.Now, dt => dt.ToString("o")).Should().BeTrue();
            ini_.ReadString("Session", "LastSeen").Should().Be(lastSeen.ToString("o"));

            ini_.GetKeys("Session").Should().Equal("User", "Password", "LastSeen");

            ini_["session", "user"].Should().Be("Jerry");

            ini_.ReadLong("server", "port").Should().Be(80);
            ini_.ReadULong("server", "port").Should().Be(80);

            ini_.Write("math", "pi", 3.14).Should().BeTrue();
            ini_.Write("math", "e", 2.71828).Should().BeTrue();
            ini_.ReadDouble("math", "pi").Should().BeApproximately(3.14, 1e-6);
            ini_.ReadDouble("math", "e").Should().BeApproximately(2.71828, 1e-6);
        }

        private string temporaryIniFilePath_;
        private IniFile ini_;
    }
}


// References:
// https://github.com/fluentassertions/fluentassertions
// https://fluentassertions.com/introduction
