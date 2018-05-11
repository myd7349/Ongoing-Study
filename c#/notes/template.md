## [Generics syntax for multiple type parameter constraints](https://stackoverflow.com/questions/965580/c-sharp-generics-syntax-for-multiple-type-parameter-constraints)
```csharp
struct DataPack<T> where T : struct
{
    T X, Y, Z;
}

class DataUnpacker<T, TDataPack>
    where T : struct
    where TDataPack : struct
{
    public T[] Unpack(TDataPack)
    {
        ...
    }
}
```

[Template specialization](https://stackoverflow.com/questions/600978/how-to-do-template-specialization-in-c-sharp)

## How can I call an overloaded method in generic method?

What I want to do is something like this:
```csharp
namespace DataModel
{
    using System;
    using System.Diagnostics;
    using System.IO;

    public class FileDataSinkProvider<TSource, TDest> : IDisposable, IDataSinkProvider<TSource>
        where TSource : struct
        where TDest : struct
    {
        public FileDataSinkProvider(string fileName, DataConverter<TSource, TDest> convert)
        {
            stream = File.Open(fileName, FileMode.Create);
            binaryWriter = new BinaryWriter(stream);

            this.convert = convert;

            AutoFlush = false;
            FlushThreshold = 0;
            counter = 0;
        }

        public void DataSink(TSource[][] data)
        {
            Debug.Assert(data != null);
            Debug.Assert(stream != null && binaryWriter != null);
            Debug.Assert(convert != null);
            Debug.Assert(!AutoFlush || FlushThreshold > 0);

            for (int i = 0; i < data.Length; ++i)
            {
                for (int j = 0; j < data[i].Length; ++j)
                    binaryWriter.Write(convert(data[i][j])); // oops!
            }

            if (AutoFlush)
            {
                counter++;

                if (counter == FlushThreshold)
                {
                    binaryWriter.Flush();
                    counter = 0;
                }
            }
        }

        public void Close()
        {
            stream.Close();
        }

        public void Dispose()
        {
            Close();
        }

        public bool AutoFlush
        {
            get;
            set;
        }

        public int FlushThreshold
        {
            get;
            set;
        }

        private Stream stream;
        private BinaryWriter binaryWriter;
        private int counter;
        private DataConverter<TSource, TDest> convert;
    }
}
```

I found these pages, both saying that you can not do it.

* [calling an overloaded method in generic method](https://stackoverflow.com/questions/22420504/calling-an-overloaded-method-in-generic-method)
* [C# cannot call overloaded non-generic method from generic method](https://stackoverflow.com/questions/3905398/c-sharp-cannot-call-overloaded-non-generic-method-from-generic-method)

So there are two solutions for me:

1. A generic BinaryWriter:
    * [Generic BinaryReader](https://stackoverflow.com/questions/9883139/generic-binaryreader)
    * [Generic BinaryReader and BinaryWriter Extensions](https://www.codeproject.com/Articles/33713/Generic-BinaryReader-and-BinaryWriter-Extensions)

2. Rewrite `FileDataSinkProvider` like this:

```csharp
namespace DataModel
{
    using System;
    using System.Diagnostics;
    using System.IO;

    public class FileDataSinkProvider<TSource, short> : IDisposable, IDataSinkProvider<TSource>
        where TSource : struct
    {
        public FileDataSinkProvider(string fileName, DataConverter<TSource, short> convert)
        {
            ...
        }

        public void DataSink(TSource[][] data)
        {
            ...
        }

        private DataConverter<TSource, short> convert;
    }
}
```