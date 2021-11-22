[Using a C++ TCP client socket on a specific network interface Linux/Unix](https://stackoverflow.com/questions/7057482/using-a-c-tcp-client-socket-on-a-specific-network-interface-linux-unix)

> ```c
> char* interface = "eth5";
> setsockopt( socket_file_descriptor_, SOL_SOCKET, SO_BINDTODEVICE, interface, 4 );
> ```

https://linux.die.net/man/2/setsockopt