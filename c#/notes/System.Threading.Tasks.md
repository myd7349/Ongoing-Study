[How and when to use ‘async’ and ‘await’](https://stackoverflow.com/questions/14455293/how-and-when-to-use-async-and-await)

[Wrapping synchronous code into asynchronous call](https://stackoverflow.com/questions/21406973/wrapping-synchronous-code-into-asynchronous-call)

[There Is No Thread](https://blog.stephencleary.com/2013/11/there-is-no-thread.html)

[Stephen Cleary — Asynchronous streams](https://www.youtube.com/watch?v=-Tq4wLyen7Q)

[AsyncIntro](https://github.com/jskeet/DemoCode/tree/main/AsyncIntro)

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

- [AsyncEx](https://github.com/StephenCleary/AsyncEx)

  - [wpf- How to wait for result from Dispatcher.invokeAsync before control is passed to next statement](https://stackoverflow.com/questions/45509478/wpf-how-to-wait-for-result-from-dispatcher-invokeasync-before-control-is-passed)

https://github.com/microsoft/Vipr/blob/master/src/Core/Vipr/FileWriter.cs

https://github.com/phatboyg/GreenPipes

https://github.com/microsoft/FASTER

[Task.Factory.StartNew vs Task.Factory.FromAsync](https://stackoverflow.com/questions/17432306/task-factory-startnew-vs-task-factory-fromasync)

[Do you have to put Task.Run in a method to make it async?](https://stackoverflow.com/questions/17119075/do-you-have-to-put-task-run-in-a-method-to-make-it-async)

[Async and Await](https://blog.stephencleary.com/2012/02/async-and-await.html)

> One important point about awaitables is this: it is the type that is awaitable, not the method returning the type. In other words, you can await the result of an async method that returns Task … because the method returns Task, not because it’s async. So you can also await the result of a non-async method that returns Task.

[ContinueWith a cancelled Task](https://stackoverflow.com/questions/11892315/continuewith-a-cancelled-task)

[8 await async mistakes that you SHOULD avoid in .NET](https://www.youtube.com/watch?v=lQu-eBIIh-w)

[What is the difference between a Nested Task and Child Task](https://stackoverflow.com/questions/20048493/what-is-the-difference-between-a-nested-task-and-child-task)

[Should I wrap a task in another task or should I just return the created task?](https://stackoverflow.com/questions/22063721/should-i-wrap-a-task-in-another-task-or-should-i-just-return-the-created-task)

[How to: Unwrap a Nested Task](https://docs.microsoft.com/en-us/dotnet/standard/parallel-programming/how-to-unwrap-a-nested-task)

[Nested task inside loop](https://stackoverflow.com/questions/18460464/nested-task-inside-loop)

[c# wrapping a Task into a another Task](https://stackoverflow.com/questions/41432566/c-sharp-wrapping-a-task-into-a-another-task)

[Chaining tasks using continuation tasks](https://docs.microsoft.com/en-us/dotnet/standard/parallel-programming/chaining-tasks-by-using-continuation-tasks)

[Is it considered acceptable to not call Dispose() on a TPL Task object?](https://stackoverflow.com/questions/3734280/is-it-considered-acceptable-to-not-call-dispose-on-a-tpl-task-object)

[Attached and Detached Child Tasks](https://docs.microsoft.com/en-us/dotnet/standard/parallel-programming/attached-and-detached-child-tasks)

ValueTask

[An Introduction to System.Threading.Channels](https://devblogs.microsoft.com/dotnet/an-introduction-to-system-threading-channels/)

[Why would one use Task<T> over ValueTask<T> in C#?](https://stackoverflow.com/questions/43000520/why-would-one-use-taskt-over-valuetaskt-in-c)

[Using async-await for database queries](https://stackoverflow.com/questions/63165599/using-async-await-for-database-queries)

[DialogHost hangs](https://github.com/MaterialDesignInXAML/MaterialDesignInXamlToolkit/issues/2751)

[C# - Making sync function to async](https://learn.microsoft.com/en-us/answers/questions/277316/c-making-sync-function-to-async.html)

[How can I "adapt" a Task<IEnumerable<T>> to IAsyncEnumerable<T>?](https://stackoverflow.com/questions/55384089/how-can-i-adapt-a-taskienumerablet-to-iasyncenumerablet)

Task.Status

[A lap around the Microsoft MVVM Toolkit](https://xamlbrewer.wordpress.com/2020/11/16/a-lap-around-the-microsoft-mvvm-toolkit/comment-page-1/)

[How would I run an async Task<T> method synchronously?](https://stackoverflow.com/questions/5095183/how-would-i-run-an-async-taskt-method-synchronously)

[How to handle Task.Run Exception](https://stackoverflow.com/questions/32067034/how-to-handle-task-run-exception)

Timeout

[TcpListener: how to stop listening while awaiting AcceptTcpClientAsync()?](https://stackoverflow.com/questions/19220957/tcplistener-how-to-stop-listening-while-awaiting-accepttcpclientasync)

[Asynchronously wait for Task<T> to complete with timeout](https://stackoverflow.com/questions/4238345/asynchronously-wait-for-taskt-to-complete-with-timeout)

[How to call asynchronous method from synchronous method in C#?](https://stackoverflow.com/questions/9343594/how-to-call-asynchronous-method-from-synchronous-method-in-c)
