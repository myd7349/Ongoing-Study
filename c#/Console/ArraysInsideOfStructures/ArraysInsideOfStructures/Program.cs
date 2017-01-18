// 2016-07-01T09:05+08:00
using System;

using Common;

/*
What is the equivalent of this C structure:
struct Data
{
    int header;
    int data[10];
}; 
in C#?
*/

namespace ArraysInsideOfStructures
{
    unsafe class Program
    {
        static void PrintData(int* data, int items)
        {
            for (int* p = data; p < data + items; p++)
                Console.Write("{0} ", *p);
        }

        // Func<T, int*> dataGetter ???
        // Func<T, object> dataGetter ??? Then convert between int* and object 
        static void PrintData<T>(int header, int *data) where T : struct
        {
            string typename = typeof(T).ToString();
            Console.WriteLine("Test {0}:", typename.Substring(typename.LastIndexOf('.') + 1));
            Console.WriteLine("\theader: {0}", header);
            Console.Write("\tdata: ");
            PrintData(data, 10);
            Console.WriteLine();
        }

        static void TestData1()
        {
            var data = new Data1();
            FillStructNative.FillStruct1(ref data);
            PrintData<Data1>(data.header, &data.elem0);
        }

        static void TestData2()
        {
            var data = new Data2();
            FillStructNative.FillStruct2(ref data);
            PrintData<Data2>(data.header, &data.data);
        }

        static void TestData3()
        {
            var data = new Data3();
            //data.data = new int[10];
            Console.WriteLine(data.data == null);
            FillStructNative.FillStruct3(ref data);
            Console.WriteLine(data.data == null);
            fixed (int* p = data.data)
            {
                PrintData<Data3>(data.header, p);
            }
        }

        static void TestData4()
        {
            var data = new Data4();
            FillStructNative.FillStruct4(ref data);
            PrintData<Data4>(data.header, data.data);
        }

        static void TestGetCwd()
        {
            var cwd = new Cwd();
            FillStructNative.GetCwd(cwd);
            Console.WriteLine(cwd.cwd);
        }

        static void Main(string[] args)
        {
            TestData1();
            TestData2();
            TestData3();
            TestData4();
            TestGetCwd();

            Util.Pause();
        }
    }
}
