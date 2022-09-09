[What is the currently best C# implementation for a Producer/Consumer scenario?](https://softwareengineering.stackexchange.com/questions/421264/what-is-the-currently-best-c-implementation-for-a-producer-consumer-scenario)

[An Introduction to System.Threading.Channels](https://devblogs.microsoft.com/dotnet/an-introduction-to-system-threading-channels/)

[Performance Showdown of Producer/Consumer (Job Queues) Implementations in C# .NET](https://michaelscodingspot.com/performance-of-producer-consumer/)

[.NET Problem using System.Threading.Channels.Channel efficiently](https://stackoverflow.com/questions/72841269/net-problem-using-system-threading-channels-channel-efficiently)

[C# Job Queues (part 2) with Reactive Extensions and Channels](https://michaelscodingspot.com/c-job-queues-with-reactive-extensions-and-channels/)

[C# Channels - Publish / Subscribe Workflows](https://deniskyashif.com/2019/12/08/csharp-channels-part-1/) - [code](https://github.com/deniskyashif/trydotnet-channels)

[C# Channels - Timeout and Cancellation](https://deniskyashif.com/2019/12/11/csharp-channels-part-2/)

> The relationship between concurrency and parallelism is commonly misunderstood. In fact, two procedures being concurrent doesn’t mean that they’ll run in parallel. The following quote by Martin Kleppmann has stood out in my mind when it comes to concurrency:
> 
>     For defining concurrency, the exact time doesn’t matter: we simply call two operations concurrent if they are both unaware of each other, regardless of the physical time at which they occurred.
> 
>     – “Designing Data-Intensive Applications” by Martin Kleppmann


> Don’t communicate by sharing memory, share memory by communicating.

[C# Channels - Async Data Pipelines](https://deniskyashif.com/2020/01/07/csharp-channels-part-3/)

[System.Threading.Channels](https://sachabarbs.wordpress.com/2018/11/28/system-threading-channels/)

[C# – Using Channel as an async queue](https://makolyte.com/event-driven-dotnet-concurrent-producer-consumer-using-a-channel-as-a-non-blocking-async-queue/)

[C# – How to batch read with Threading.ChannelReader](https://makolyte.com/csharp-how-to-batch-read-with-threading-channelreader/)

[C# – Example of using BlockingCollection](https://makolyte.com/event-driven-dotnet-concurrent-producer-consumer-using-blockingcollection/)

[System.Threading.Channels. Ability to delete an item from channel queue only after its successful processing](https://github.com/dotnet/runtime/issues/31182)

[How to make count available on .NET Channel](https://stackoverflow.com/questions/70375696/how-to-make-count-available-on-net-channel)
