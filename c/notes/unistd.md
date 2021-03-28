[Sleep for milliseconds](https://stackoverflow.com/questions/4184468/sleep-for-milliseconds)

https://github.com/lichuang/libraft/blob/11cb7dfb69c83ad0000671ad481e6bb63f4d3cbe/src/base/file_system_adaptor.cc#L10-L13

```c
bool 
PosixFileSystemAdaptor::PathExists(const string& path) {
  return access(path.c_str(), F_OK) == 0;
}
```

