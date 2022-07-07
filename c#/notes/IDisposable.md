[GitHub - DotNetAnalyzers/IDisposableAnalyzers: Roslyn analyzers for IDisposable](https://github.com/DotNetAnalyzers/IDisposableAnalyzers)

[Is it abusive to use IDisposable and “using” as a means for getting “scoped behavior” for exception safety?](https://stackoverflow.com/questions/2101524/is-it-abusive-to-use-idisposable-and-using-as-a-means-for-getting-scoped-beha)

[Using IDisposable for managing a reference count](https://stackoverflow.com/questions/25827668/using-idisposable-for-managing-a-reference-count)

[C# Reference Counting](https://stackoverflow.com/questions/35005219/c-sharp-reference-counting)

[Managing unmanaged objects in C#](https://medium.com/ingeniouslysimple/managing-unmanaged-objects-in-c-6c69968c60eb)

[When to call Dispose](https://blogs.msdn.microsoft.com/kimhamil/2008/11/06/when-to-call-dispose/)

[WinForms - when to call Dispose? When is it implicit?](https://stackoverflow.com/questions/22846663/winforms-when-to-call-dispose-when-is-it-implicit)

[CA1063: Implement IDisposable correctly](https://docs.microsoft.com/en-us/dotnet/fundamentals/code-analysis/quality-rules/ca1063)

```csharp
public class Resource : IDisposable
{
    private bool isDisposed;
    private IntPtr nativeResource = Marshal.AllocHGlobal(100);
    private AnotherResource managedResource = new AnotherResource();

    // Dispose() calls Dispose(true)
    public void Dispose()
    {
        Dispose(true);
        GC.SuppressFinalize(this);
    }

    // The bulk of the clean-up code is implemented in Dispose(bool)
    protected virtual void Dispose(bool disposing)
    {
        if (isDisposed) return;

        if (disposing)
        {
            // free managed resources
            managedResource.Dispose();
        }

        // free native resources if there are any.
        if (nativeResource != IntPtr.Zero)
        {
            Marshal.FreeHGlobal(nativeResource);
            nativeResource = IntPtr.Zero;
        }

        isDisposed = true;
    }

    // NOTE: Leave out the finalizer altogether if this class doesn't
    // own unmanaged resources, but leave the other methods
    // exactly as they are.
    ~Resource()
    {
        // Finalizer calls Dispose(false)
        Dispose(false);
    }
}
```

[Implement a Dispose method](https://docs.microsoft.com/en-us/dotnet/standard/garbage-collection/implementing-dispose)

[Proper use of the IDisposable interface](https://stackoverflow.com/questions/538060/proper-use-of-the-idisposable-interface)

[close or dispose](https://stackoverflow.com/questions/4153595/close-or-dispose)

https://github.com/reactiveui/splat/blob/main/src/Splat/Disposables/BooleanDisposable.cs

[c# open file with default application and parameters](https://stackoverflow.com/questions/11365984/c-sharp-open-file-with-default-application-and-parameters)

```csharp
public static void OpenWithDefaultProgram(string path)
{
    using Process fileopener = new Process();

    fileopener.StartInfo.FileName = "explorer";
    fileopener.StartInfo.Arguments = "\"" + path + "\"";
    fileopener.Start();
}
```

[What scope does a using statement have without curly braces](https://stackoverflow.com/questions/24819576/what-scope-does-a-using-statement-have-without-curly-braces)

https://github.com/StephenCleary/Disposables

https://learn.microsoft.com/en-us/dotnet/api/system.printing.printsystemobject.internaldispose?view=windowsdesktop-7.0

https://github.com/dotnet/wpf/blob/main/src/Microsoft.DotNet.Wpf/src/System.Printing/CPP/src/PrintQueue.cpp

```csharp
namespace System.Printing
{
    public abstract class PrintSystemObject : IDisposable
    {
        ~PrintSystemObject();

        protected bool IsDisposed { get; set; }

        public sealed override void Dispose();

        protected virtual void Dispose(bool A_0);

        protected virtual void InternalDispose(bool disposing);
    }
}

namespace System.Printing
{
    public class PrintQueue : PrintSystemObject
    {
        protected sealed override void InternalDispose(bool disposing);
    }
}
```

https://github.com/dotnet/runtime/blob/main/src/libraries/System.Net.Sockets/src/System/Net/Sockets/NetworkStream.cs

```csharp
// Whether Dispose has been called. 0 == false, 1 == true
private int _disposed;
```
