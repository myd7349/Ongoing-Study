Projects using `ZeroMQ`:

- https://github.com/circus-tent/circus
- https://github.com/facontidavide/PlotJuggler/tree/main/plotjuggler_plugins/DataStreamZMQ
- [Open3D](https://github.com/isl-org/Open3D)

Tools:

- [zmtpdump](https://github.com/zeromq/zmtpdump): ZeroMQ Transport Protocol packet analyzer.

Issues:

- [zmq will crash in Windows 10 with non-English user name(e.g. a Chinese user name) · Issue #4356 · zeromq/libzmq · GitHub](https://github.com/zeromq/libzmq/issues/4356)
  
  - [Fix crash in context with wide characters in path by saschavv · Pull Request #4235 · zeromq/libzmq · GitHub](https://github.com/zeromq/libzmq/pull/4235)
  
  - [AF_UNIX comes to Windows - Windows Command Line](https://devblogs.microsoft.com/commandline/af_unix-comes-to-windows/)
    
    > There are three different addressing formats for unix sockets. ‘pathname’, ‘abstract’ and ‘unnamed’ sockets. ‘pathname’ sockets are bound to the filesystem, where in the ‘sun_path’
    >  member of the struct is used to specify a null-terminated UTF-8 file 
    > system path. You can expect the same from the Windows implementation, where ‘sun_path’ specifies a Win32 UTF-8 file system path.