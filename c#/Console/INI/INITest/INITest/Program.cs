namespace INITest
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Linq;
    using System.Reflection;
    using System.Text;

    using Common;
    using Common.IO;

    class Program
    {
        static string AppBaseDirectory = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location);

        static void Main(string[] args)
        {
            Test1();

            TestLongestValueCanBeWritten();
            TestLongestValueCanBeWritten("又赢了！", Encoding.GetEncoding("gb2312"));

            TestLongestValueCanBeRead();
            TestLongestValueCanBeRead("又赢了！");

            TestIniFileClass();

            TestIniFileClass2();

            Console.ReadKey();
        }

        static void Test1()
        {
            Console.WriteLine("---------- {0} ----------", DiagnosticsHelper.GetCurrentMethodName());

            var iniFilePath = Path.Combine(AppBaseDirectory, "test1.ini");

            Kernel32.WritePrivateProfileString(null, "tom", "jerry", iniFilePath);
            Kernel32.WritePrivateProfileString("hello", "hello", "hello", iniFilePath);
            Kernel32.WritePrivateProfileString("hello", "world", "world", iniFilePath);
            Kernel32.WritePrivateProfileString("hello", "answer", "42", iniFilePath);
            Kernel32.WritePrivateProfileString("hello", "empty", "", iniFilePath);
            Kernel32.WritePrivateProfileString("foo", "foo", "foo", iniFilePath);
            Kernel32.WritePrivateProfileString("bar", "bar", "bar", iniFilePath);

            foreach (var section in Kernel32.GetPrivateProfileSectionNames(iniFilePath))
                Console.WriteLine("Section: {0}", section);

            foreach (var section in Kernel32.GetPrivateProfileString(null, null, null, iniFilePath).ToStrings())
                Console.WriteLine("Section: {0}", section);

            foreach (var key in Kernel32.GetPrivateProfileString("hello", null, null, iniFilePath).ToStrings())
                Console.WriteLine("Key: {0}", key);

            Console.WriteLine(Kernel32.GetPrivateProfileInt("Hello", "Answer", 0, iniFilePath));

            Console.WriteLine(Kernel32.GetPrivateProfileString("bang", "ghost", null, iniFilePath));
        }

        static void TestLongestValueCanBeWritten(string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", Encoding encoding = null)
        {
            Console.WriteLine("---------- {0} ----------", DiagnosticsHelper.GetCurrentMethodName());
            Console.WriteLine("Chars: {0}", chars);

            int lowerBound = 0;
            int upperBound = ushort.MaxValue + 1000;

            var random = new Random();

            while (lowerBound <= upperBound)
            {
                var middle = (lowerBound + upperBound) / 2;

                var iniFilePath = Path.Combine(AppBaseDirectory,
                    string.Format("test-longest-value-can-be-written-{0}-{1}.ini", middle, chars));

#if false
                var value = new string('A', middle);
#else
                var value = random.RandomString(middle, chars);
#endif
                if (!Kernel32.WritePrivateProfileString("Section", "K", value, iniFilePath))
                    break;

                var result = IOHelper.EnumerateLines(iniFilePath, encoding).Skip(1).Take(1).FirstOrDefault();
                result = result.Substring(2);
                
                if (result == value)
                {
                    Console.WriteLine("Length {0}: OK.", middle);
                    lowerBound = middle + 1;
                }
                else
                {
                    Console.WriteLine("Length {0}: Not OK!", middle);
                    upperBound = middle - 1;
                }
            }
        }

        static void TestLongestValueCanBeRead(string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")
        {
            Console.WriteLine("---------- {0} ----------", DiagnosticsHelper.GetCurrentMethodName());
            Console.WriteLine("Chars: {0}", chars);

            int lowerBound = 0;
            int upperBound = ushort.MaxValue + 1000;

            var random = new Random();

            while (lowerBound <= upperBound)
            {
                var middle = (lowerBound + upperBound) / 2;

                var iniFilePath = Path.Combine(AppBaseDirectory,
                    string.Format("test-longest-value-can-be-read-{0}-{1}.ini", middle, chars));

#if false
                var value = new string('A', middle);
#else
                var value = random.RandomString(middle, chars);
#endif
                if (!Kernel32.WritePrivateProfileString("Section", "K", value, iniFilePath))
                    break;

                var result = Kernel32.GetPrivateProfileString("Section", "K", null, iniFilePath);
                if (result == value)
                {
                    Console.WriteLine("Length {0}: OK.", middle);
                    lowerBound = middle + 1;
                }
                else
                {
                    Console.WriteLine("Length {0}: Not OK!", middle);
                    upperBound = middle - 1;
                }
            }
        }

        static void TestIniFileClass()
        {
            Console.WriteLine("---------- {0} ----------", DiagnosticsHelper.GetCurrentMethodName());

            var iniFilePath = Path.Combine(AppBaseDirectory, "config.ini");

            var ini = new IniFile(iniFilePath);
            foreach (var kv in ini.ReadSection("hello"))
                Console.WriteLine("{0} = {1}", kv.Key, kv.Value);

            Console.WriteLine("{0}", ini.HasSection("server"));
            Console.WriteLine("{0}", ini.HasKey("server", "user"));

            ini.WriteSection(
                "Server",
                new KeyValuePair<string, string>[]
                {
                    new KeyValuePair<string, string>("IP", "127.0.0.1"),
                    new KeyValuePair<string, string>("Port", "80"),
                    new KeyValuePair<string, string>("User", ""),
                });
            foreach (var kv in ini.ReadSection("Server"))
                Console.WriteLine("{0} = {1}", kv.Key, kv.Value);

            Console.WriteLine("{0}", ini.HasSection("server"));
            Console.WriteLine("{0}", ini.HasKey("server", "user"));
        }

        static void TestIniFileClass2()
        {
            Console.WriteLine("---------- {0} ----------", DiagnosticsHelper.GetCurrentMethodName());

            var iniFilePath = Path.Combine(AppBaseDirectory, "config2.ini");

            var config =
@"[Server]
User=
IP =127.0.0.1
Port=80
[Login]
User=admin
Pwd=123456
";
            using (var configStream = config.ToStream())
            {
                var configContents = IniFile2.Load(configStream);
                foreach (var kv in configContents)
                    Console.WriteLine("{0} = {1}", kv.Key, kv.Value);

                using (var iniFileStream = new FileStream(iniFilePath, FileMode.Create))
                    IniFile2.Store(configContents, iniFileStream, Encoding.UTF8);

                using (var ini = new IniFile2(iniFilePath, Encoding.UTF8))
                {
                    ini["login", "LastSeen"] = DateTime.Now.ToString();
                    foreach (var section in ini.GetSections())
                        Console.WriteLine("Section: {0}", section);

                    Console.WriteLine("Port: {0}", ini.ReadInt("server", "port"));
                }
            }
        }
    }
}
