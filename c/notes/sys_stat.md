https://github.com/lichuang/libraft/blob/11cb7dfb69c83ad0000671ad481e6bb63f4d3cbe/src/base/file_system_adaptor.cc#L15-L22

```c
bool 
PosixFileSystemAdaptor::DirectoryExists(const string& dir) {
  struct stat buf;
  if (::stat(dir.c_str(), &buf) == 0) {
    return S_ISDIR(buf.st_mode);
  }
  return false;
}
```

