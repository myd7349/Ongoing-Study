[TcpListener Timeout/about/something? Without ASync?](https://stackoverflow.com/questions/3313313/tcplistener-timeout-about-something-without-async)

[Socket.Select Method](https://learn.microsoft.com/en-us/dotnet/api/system.net.sockets.socket.select?view=net-6.0)

https://github.com/dotnet/runtime/blob/main/src/libraries/System.Net.Sockets/src/System/Net/Sockets/NetworkStream.cs

```
if (!socket.Blocking)
{
    // Stream.Read*/Write* are incompatible with the semantics of non-blocking sockets, and
    // allowing non-blocking sockets could result in non-deterministic failures from those
    // operations. A developer that requires using NetworkStream with a non-blocking socket can
    // temporarily flip Socket.Blocking as a workaround.
    throw new IOException(SR.net_sockets_blocking);
}
```

[Why should I use non-blocking or blocking sockets?](https://stackoverflow.com/questions/10654286/why-should-i-use-non-blocking-or-blocking-sockets)

[TcpListener: how to stop listening while awaiting AcceptTcpClientAsync()?](https://stackoverflow.com/questions/19220957/tcplistener-how-to-stop-listening-while-awaiting-accepttcpclientasync)

[Asynchronously wait for Task<T> to complete with timeout](https://stackoverflow.com/questions/4238345/asynchronously-wait-for-taskt-to-complete-with-timeout)

[How do I interrupt Socket.Select](https://stackoverflow.com/questions/26290117/how-do-i-interrupt-socket-select)

[Socket.Shutdown(SocketShutdown) Method](https://learn.microsoft.com/en-us/dotnet/api/system.net.sockets.socket.shutdown?view=net-6.0)

> When using a connection-oriented Socket, always call the Shutdown method before closing the Socket. This ensures that all data is sent and received on the connected socket before it is closed.
>
> Call the Close method to free all managed and unmanaged resources associated with the Socket. Do not attempt to reuse the Socket after closing.
