[What is the use for Task.FromResult in C#](https://stackoverflow.com/questions/19568280/what-is-the-use-for-task-fromresulttresult-in-c-sharp)

[Task.FromResult应用场景举例](https://www.cnblogs.com/darrenji/p/4712504.html)

Note that:

```csharp
Task.Run(() => SomeSyncFunction());
```

can not be replaced with:

```csharp
Task.FromResult(SomeSyncFunction());
```

[Task.FromResult() vs. Task.Run()](https://stackoverflow.com/questions/34005397/task-fromresult-vs-task-run)

[Using Task.FromResult v/s await in C#](https://stackoverflow.com/questions/50726867/using-task-fromresult-v-s-await-in-c-sharp)

[Task.FromException](https://docs.microsoft.com/en-us/dotnet/api/system.threading.tasks.task.fromresult?view=net-5.0)

> ```csharp
> private static Task<long> GetFileLengthsAsync(string filePath)
> {
>     if (! Directory.Exists(filePath))
>     {
>         return Task.FromException<long>(
>             new DirectoryNotFoundException("Invalid directory name."));
>     }
>     else {
>         string[] files = Directory.GetFiles(filePath);
>         if (files.Length == 0)
>             return Task.FromResult(0L);
>         else
>             return Task.Run(() =>
>             {
>                 long total = 0;
>                 Parallel.ForEach(files, (fileName) =>
>                 {
>                     var fs = new FileStream(fileName, FileMode.Open,
>                                             FileAccess.Read, FileShare.ReadWrite,
>                                             256, true);
>                     long length = fs.Length;
>                     Interlocked.Add(ref total, length);
>                     fs.Close();
>                 });
>                 return total;
>             });
>     }
> }
> ```

Packages:

- [AsyncAwaitBestPractices](https://github.com/brminnick/AsyncAwaitBestPractices)

https://github.com/microsoft/Vipr/blob/master/src/Core/Vipr/FileWriter.cs

https://github.com/phatboyg/GreenPipes

https://github.com/microsoft/FASTER
