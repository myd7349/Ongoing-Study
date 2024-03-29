https://github.com/dotnet/ClangSharp/blob/main/tests/ClangSharp.UnitTests/InteropTests/CXStringTests.cs

```csharp
public static void SizeOfTest()
{
    if (Environment.Is64BitProcess)
    {
        Assert.That(sizeof(CXString), Is.EqualTo(16));
    }
    else
    {
        Assert.That(sizeof(CXString), Is.EqualTo(8));
    }
}
```

https://github.com/FantasticFiasco/mvvm-dialogs/blob/v8.0.0/src/net/FrameworkDialogs/FolderBrowser/FolderBrowserDialogSettings.cs

```csharp
public Environment.SpecialFolder RootFolder { get; set; } = Environment.SpecialFolder.Desktop;
```

https://github.com/AgigoNoTana/HiddenDesktopViewer/blob/master/HiddenDesktopViewer/Form1.cs#L754

```csharp
System.Environment.Is64BitProcess;
System.Environment.Is64BitOperatingSystem;
```

http://www.eggheadcafe.com/articles/20031219.asp

> System.Environment.CurrentDirectory

Environment.StackTrace

https://github.com/benaadams/Ben.Demystifier/

[How to print the current Stack Trace in .NET without any exception?](https://stackoverflow.com/questions/531695/how-to-print-the-current-stack-trace-in-net-without-any-exception)

Environment.ProcessPath

[Find the location of my application's executable in WPF (C# or vb.net)?](https://stackoverflow.com/questions/3123870/find-the-location-of-my-applications-executable-in-wpf-c-or-vb-net/)
