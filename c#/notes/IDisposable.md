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