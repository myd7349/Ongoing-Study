[SwitchToThread/Thread.Yield vs. Thread.Sleep(0) vs. Thead.Sleep(1)](https://stackoverflow.com/questions/1413630/switchtothread-thread-yield-vs-thread-sleep0-vs-thead-sleep1)

[Thread.Sleep(0) vs Sleep(1) vs Yeild](https://www.cnblogs.com/stg609/p/3857242.html)

C# 9.0 in a Nutshell

> Thread.Sleep(0) relinquishes the thread’s current time slice immediately, voluntarily handing over the CPU to other threads. Thread.Yield() does the same thing except that it relinquishes only to threads running on the same processor.

[Unhandled Exception in Winforms Application](https://stackoverflow.com/questions/5049063/unhandled-exception-in-winforms-application)

[Microsoft.VisualStudio.Threading](https://github.com/microsoft/vs-threading)

[SwitchToThread/Thread.Yield vs. Thread.Sleep(0) vs. Thead.Sleep(1)](https://stackoverflow.com/questions/1413630/switchtothread-thread-yield-vs-thread-sleep0-vs-thead-sleep1)

[High resolution timer in C#](https://stackoverflow.com/questions/24839105/high-resolution-timer-in-c-sharp)

> There is an option: use `Thread.Sleep(0)`. Attempt to call `Thread.Sleep(1)` or employ a `System.Threading.Timer` would always come down to system timer resolution.

> `Thread.Yield()` will reduce the chance of a context-switch. `Thread.Sleep(0)` results in a context switch to lower priority processes. Elevating the current process priority will decrease the chance of `Thread.Yield()` itself context-switching.

[Why does Interlocked.Exchange not support Boolean type?](https://stackoverflow.com/questions/6164751/why-does-interlocked-exchange-not-support-boolean-type)

[C# producer/consumer](https://stackoverflow.com/questions/1656404/c-sharp-producer-consumer)

[C# Is value type assignment atomic?](https://stackoverflow.com/questions/53601121/c-sharp-is-value-type-assignment-atomic)

> Reads and writes of the following data types are atomic: *bool*, *char*,  *byte*, *sbyte*, *short*, *ushort*, *uint*, *int*, *float*, and *reference types*. In  addition, reads and writes of *enum types* with an underlying type in  the previous list are also atomic. Reads and writes of other types,  including *long*, *ulong*, *double*, and *decimal*, as well as user-defined  types, are not guaranteed to be atomic. Aside from the library  functions designed for that purpose, there is no guarantee of atomic  read-modify-write, such as in the case of increment or decrement.

[Is ++ operation atomic in C#?](https://stackoverflow.com/questions/17872057/is-operation-atomic-in-c)

> No ++/-- is not an atomic operation, however reading and writing to  integers and other primitive times is considered an atomic operation.

[Difference in usage and implementation of ManualResetEvent(Slim), Semaphore(Slim) and ReaderWriterLock(Slim)](https://stackoverflow.com/questions/6764864/difference-in-usage-and-implementation-of-manualreseteventslim-semaphoreslim)

> `ReaderWriterLockSlim` is a better version of `ReaderWriterLock` that is faster and  doesn't suffer from writer starvation
>
> `ManualResetEventSlim` and `SemaphoreSlim` are fully managed versions of a `ManualResetEvent` and `Semaphore` that spin-wait for a while before falling back to kernel objects, and  so are faster than the old versions when wait times are short.

[What's the difference between Invoke() and BeginInvoke()](https://stackoverflow.com/questions/229554/whats-the-difference-between-invoke-and-begininvoke)

> `Control.Invoke`: Executes on the UI thread, but calling thread waits for completion before continuing.
>
> `Control.BeginInvoke`: Executes on the UI thread, and calling thread doesn't wait for completion.

[Thread.GetNamedDataSlot(String) Method](https://docs.microsoft.com/en-us/dotnet/api/system.threading.thread.getnameddataslot?view=net-5.0)

- https://github.com/dotnet/runtime/blob/6b11f64ec09983013862c2fd85ba29c940c44eea/src/libraries/System.Drawing.Common/src/System/Drawing/Gdiplus.cs#L47-L61

[Recursive (Re-entrant) Locks](https://blog.stephencleary.com/2013/04/recursive-re-entrant-locks.html)

> Traditionally, recursive locks have been the default on Microsoft platforms. The `lock` statement, `Monitor`, `Mutex`, and `ReaderWriterLock` are all recursive. However, newer types are starting to change this; `SpinLock` is not recursive, and `ReaderWriterLockSlim` is not recursive by default (it does provide recursion as an option).

https://github.com/microsoft/vs-threading

https://github.com/microsoft/coyote

[C# Thread safe fast(est) counter](https://stackoverflow.com/questions/13181740/c-sharp-thread-safe-fastest-counter)

```csharp
return Interlocked.Increment(ref COUNTER);
```

[Cancelling a Task is throwing an exception](https://stackoverflow.com/questions/7343211/cancelling-a-task-is-throwing-an-exception)

[Is a reference assignment threadsafe?](https://stackoverflow.com/questions/5209623/is-a-reference-assignment-threadsafe)

[ThreadStart with parameters](https://stackoverflow.com/questions/1195896/threadstart-with-parameters)

#### Interlocked

[C# thread safety of global configuration settings](https://stackoverflow.com/questions/922715/c-sharp-thread-safety-of-global-configuration-settings)

[C# Interlocked](https://thith.blogspot.com/2005/11/c-interlocked.html)

[Is a reference assignment threadsafe?](https://stackoverflow.com/questions/5209623/is-a-reference-assignment-threadsafe)

[Atomicity, Interlocked & Memory Operation Optimizations in C#](https://mangcut.vn/blog/2015-02-14-atomicity-interlocked-memory-operation-optimizations-csharp.html)

[Why does Interlocked.Exchange not support Boolean type?](https://stackoverflow.com/questions/6164751/why-does-interlocked-exchange-not-support-boolean-type)

[reference assignment is atomic so why is Interlocked.Exchange(ref Object, Object) needed?](https://stackoverflow.com/questions/2192124/reference-assignment-is-atomic-so-why-is-interlocked-exchangeref-object-object)

[Using Interlocked.CompareExchange with a class](https://stackoverflow.com/questions/6690386/using-interlocked-compareexchange-with-a-class)

[Is double read atomic on an Intel architecture?](https://stackoverflow.com/questions/24731791/is-double-read-atomic-on-an-intel-architecture)

[Is reading a double not thread-safe?](https://stackoverflow.com/questions/3676808/is-reading-a-double-not-thread-safe)

> If you want to avoid writing use compareExchange.
> 
> Interlocked.CompareExchange(ref somevariable, somevalue, somevalue);

[How do I atomically swap 2 ints in C#?](https://stackoverflow.com/questions/3855671/how-do-i-atomically-swap-2-ints-in-c)

#### volatile

[When should the volatile keyword be used in C#?](https://stackoverflow.com/questions/72275/when-should-the-volatile-keyword-be-used-in-c)

[Atomicity, volatility and immutability are different, part three](https://ericlippert.com/2011/06/16/atomicity-volatility-and-immutability-are-different-part-three/)

["A reference to a volatile field will not be treated as volatile" implications](https://stackoverflow.com/questions/425132/a-reference-to-a-volatile-field-will-not-be-treated-as-volatile-implications)

```csharp
volatile int a;
volatile int b;

SwapHelper.Swap(ref a, ref b);
```
