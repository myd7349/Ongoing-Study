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
