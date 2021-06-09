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

So there are four solutions for me:

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

3. Use `dynamic` expression:
```csharp
binaryWriter.Write((dynamic)convert(data[i][j]));
```

4. Hard work!
```csharp
namespace ECGKit.Acquisition.DataModel
{
    using System;
    using System.Diagnostics;
    using System.IO;

    public abstract class FileDataSinkProvider<TSource, TDest> : IDisposable, IDataSinkProvider<TSource>
        where TSource : struct
        where TDest : struct
    {
        public void DataSink(TSource[][] data)
        {
            Debug.Assert(data != null);
            Debug.Assert(stream != null && binaryWriter != null);
            Debug.Assert(convert != null);
            Debug.Assert(!AutoFlush || FlushThreshold > 0);

            for (int i = 0; i < data.Length; ++i)
            {
                for (int j = 0; j < data[i].Length; ++j)
                {
                    Write(binaryWriter, convert(data[i][j]));
                }
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

        protected abstract void Write(BinaryWriter binaryWriter, TDest x);
    }

    public class FileDataSinkProvider_Short<TSource> : FileDataSinkProvider<TSource, short>
        where TSource : struct
    {
        public FileDataSinkProvider_Short(string fileName, DataConverter<TSource, short> convert)
            : base(fileName, convert)
        {
        }

        protected override void Write(BinaryWriter binaryWriter, short x)
        {
            binaryWriter.Write(x);
        }
    }

    public class FileDataSinkProvider_Double<TSource> : FileDataSinkProvider<TSource, double>
        where TSource : struct
    {
        public FileDataSinkProvider_Double(string fileName, DataConverter<TSource, double> convert)
            : base(fileName, convert)
        {
        }

        protected override void Write(BinaryWriter binaryWriter, double x)
        {
            binaryWriter.Write(x);
        }
    }
}
```

Finally, I got:
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

            for (int i = 0; i < data[0].Length; ++i)
            {
                for (int j = 0; j < data.Length; ++j)
                {
                    Write(binaryWriter, convert(data[j][i]));
                }
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

        protected virtual void Write(BinaryWriter binaryWriter, TDest x)
        {
            binaryWriter.Write((dynamic)x);
        }

        private Stream stream;
        private BinaryWriter binaryWriter;

        private int counter;
        private DataConverter<TSource, TDest> convert;
    }

    public class FileDataSinkProvider_Short<TSource> : FileDataSinkProvider<TSource, short>
        where TSource : struct
    {
        public FileDataSinkProvider_Short(string fileName, DataConverter<TSource, short> convert)
            : base(fileName, convert)
        {
        }

        protected override void Write(BinaryWriter binaryWriter, short x)
        {
            binaryWriter.Write(x);
        }
    }

    public class FileDataSinkProvider_Double<TSource> : FileDataSinkProvider<TSource, double>
        where TSource : struct
    {
        public FileDataSinkProvider_Double(string fileName, DataConverter<TSource, double> convert)
            : base(fileName, convert)
        {
        }

        protected override void Write(BinaryWriter binaryWriter, double x)
        {
            binaryWriter.Write(x);
        }
    }
}
```

[C# Define base class by ](https://stackoverflow.com/questions/30038028/c-sharp-define-base-class-by-t)

> class HDF5Exception<T> : T where T : Exception {};