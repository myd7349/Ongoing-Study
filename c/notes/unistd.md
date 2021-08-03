[Sleep for milliseconds](https://stackoverflow.com/questions/4184468/sleep-for-milliseconds)

https://github.com/lichuang/libraft/blob/11cb7dfb69c83ad0000671ad481e6bb63f4d3cbe/src/base/file_system_adaptor.cc#L10-L13

```c
bool 
PosixFileSystemAdaptor::PathExists(const string& path) {
  return access(path.c_str(), F_OK) == 0;
}
```

[fork for Windows](https://github.com/nemequ/munit/issues/2)

- https://groups.google.com/forum/#!topic/microsoft.public.win32.programmer.kernel/ejtHCZmdyaI
- https://github.com/jonclayden/multicore/blob/master/src/forknt.c
