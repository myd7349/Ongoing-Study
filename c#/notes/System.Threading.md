[SwitchToThread/Thread.Yield vs. Thread.Sleep(0) vs. Thead.Sleep(1)](https://stackoverflow.com/questions/1413630/switchtothread-thread-yield-vs-thread-sleep0-vs-thead-sleep1)

[Thread.Sleep(0) vs Sleep(1) vs Yeild](https://www.cnblogs.com/stg609/p/3857242.html)

[Unhandled Exception in Winforms Application](https://stackoverflow.com/questions/5049063/unhandled-exception-in-winforms-application)

[Microsoft.VisualStudio.Threading](https://github.com/microsoft/vs-threading)

[SwitchToThread/Thread.Yield vs. Thread.Sleep(0) vs. Thead.Sleep(1)](https://stackoverflow.com/questions/1413630/switchtothread-thread-yield-vs-thread-sleep0-vs-thead-sleep1)

[High resolution timer in C#](https://stackoverflow.com/questions/24839105/high-resolution-timer-in-c-sharp)

> There is an option: use `Thread.Sleep(0)`. Attempt to call `Thread.Sleep(1)` or employ a `System.Threading.Timer` would always come down to system timer resolution.

> `Thread.Yield()` will reduce the chance of a context-switch. `Thread.Sleep(0)` results in a context switch to lower priority processes. Elevating the current process priority will decrease the chance of `Thread.Yield()` itself context-switching.

