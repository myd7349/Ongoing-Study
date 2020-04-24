namespace Common
{
    public interface IProgressReporter<T>
    {
        void Report(T value);
    }
}

// References:
// https://stackoverflow.com/questions/38719345/iprogresst-in-net-4-0
// https://github.com/dotnet/runtime/blob/master/src/libraries/System.Private.CoreLib/src/System/IProgress.cs
// [The Progress Reporting Pattern in C# 5 async, How to use it and how it works. By Nicholas Butler](http://simplygenius.net/Article/AncillaryAsyncProgress)
