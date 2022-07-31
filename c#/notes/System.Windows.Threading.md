[Deadlock when thread uses dispatcher and the main thread is waiting for thread to finish](https://stackoverflow.com/questions/24211934/deadlock-when-thread-uses-dispatcher-and-the-main-thread-is-waiting-for-thread-t)

> Short answer: use `BeginInvoke()` instead of `Invoke()`.  Long answer change your approach: see the altenative.
>
> Currently your `Thread.Join()` is causing that main thread get blocked waiting for the termination of secondary thread, but  secondary thread is waiting to main thread executes your AppendText  action, thus your app is deadlocked. 
>
> If you change to `BeginInvoke()` then your seconday thread will not wait until main thread executes your action. Instead of this,  it will queue your invocation and continues. Your main thread will not  blocked on Join() because your seconday thread this time ends  succesfully. Then, when main thread completes this method will be free  to process the queued invocation to AppendText
>
> Alternative:
>
> ```cs
> void DoSomehtingCool()
> {
>     var factory = new TaskFactory(TaskScheduler.FromCurrentSynchronizationContext());
>     factory.StartNew(() =>
>     {
>         var result = await IntensiveComputing();
>         txtLog.AppendText("Result of the computing: " + result);
>     });
> }
> 
> async Task<double> IntensiveComputing()
> {
>     Thread.Sleep(5000);
>     return 20;
> }
> ```

[InvokeRequired in wpf](https://stackoverflow.com/questions/15504826/invokerequired-in-wpf)

> In WPF, the Invoke method is on the dispatcher, so you need to call Dispatcher.Invoke instead of Invoke. Also, there is no InvokeRequired property, but the dispatcher has a CheckAccess method (for some reason, it's hidden in intellisense). So your code should be:

[Learn more about how WPF Dispatcher works.(Invoke and InvokeAsync)](https://getandplay.github.io/2019/05/16/Learn-more-about-how-WPF-Dispatcher-works-Invoke-and-InvokeAsync/)

[深入了解 WPF Dispatcher 的工作原理（Invoke/InvokeAsync 部分）](https://blog.walterlv.com/post/dotnet/2017/09/26/dispatcher-invoke-async.html)

[Dispatcher.Invoke from a new thread is locking my UI](https://stackoverflow.com/questions/8527778/dispatcher-invoke-from-a-new-thread-is-locking-my-ui)

```csharp
private void MainWindow_Loaded(object sender, RoutedEventArgs e)
{
    var context = SynchronizationContext.Current;
    Task.Run(() =>
    {
        var i = 0;
        while (true)
        {
            context.Post((tmp) =>
            {
                uiText.Text = $"{i}";
            }), this);

            Thread.Sleep(1000);
            i++;

        }
    });

}
```

[C# Deadlocks in Depth – Part 2](https://michaelscodingspot.com/c-deadlocks-in-depth-part-2/)

[Running Action asynchronous on Dispatcher won't finish or freezes UI](https://stackoverflow.com/questions/38723085/running-action-asynchronous-on-dispatcher-wont-finish-or-freezes-ui)

> Task.Run will execute work on a background thread, and Dispatcher.InvokeAsync will turn around and execute work on a UI thread.

[What operations are atomic in C#?](https://stackoverflow.com/questions/11745440/what-operations-are-atomic-in-c)

[Why does the Interlocked.Add() method have to return a value?](https://stackoverflow.com/questions/28850481/why-does-the-interlocked-add-method-have-to-return-a-value)

[How can I dispatch same method to be called multiple times and give call order number as parameter in WPF app?](https://stackoverflow.com/questions/49288704/how-can-i-dispatch-same-method-to-be-called-multiple-times-and-give-call-order-n)

> All delegate style code blocks in .net have the same scenario. If you are passing an iterated variable, it does not get evaluated until the code block is executed. You think it gets evaluated when you create the code block, but its a misreading of the code

```csharp
void ThreadCallback()
{
    var id = 0;

    while (keepRunning)
    {
        Dispatcher.InvokeAsync(
            () => DoWorkOnUIThread(id));

        id += 1;
    }
}

int lastId = -1;

void DoWorkOnUIThread(int id)
{
    if (id != lastId + 1)
        Debug.WriteLine($"{lastId} -> {id}");

    lastId = id;
}
```

vs:

```csharp
void ThreadCallback()
{
    var id = 0;

    while (keepRunning)
    {
        var currentId = id;
        Dispatcher.InvokeAsync(
            () => DoWorkOnUIThread(currentId));

        id += 1;
    }
}

int lastId = -1;

void DoWorkOnUIThread(int id)
{
    if (id != lastId + 1)
        Debug.WriteLine($"{lastId} -> {id}");

    lastId = id;
}
```

[Dispatcher.Invoke from a new thread is locking my UI](https://stackoverflow.com/questions/8527778/dispatcher-invoke-from-a-new-thread-is-locking-my-ui)

[WPF Dispatcher.Invoke 'hanging'](https://stackoverflow.com/questions/264163/wpf-dispatcher-invoke-hanging)

```csharp
public MainWindowViewModel : ObservableObject
{
    private int status_ = 0;

    public int Status
    {
        get => status_;
        set => Dispatcher.InvokeAsync(() => SetProperty(ref status_, value));
    }

    private void StartThread()
    {
        var thread = new Thread(ThreadCallback);
        // ...
    }

    private void ThreadCallback()
    {
        Status = 404;

        Trace.WriteLine($"{Status}"); // 0
    }
}
```
