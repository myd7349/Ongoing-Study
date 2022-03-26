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
