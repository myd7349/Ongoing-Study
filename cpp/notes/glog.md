[Logging From Shared Libraries on Windows](https://github.com/google/glog/issues/83)

> I have a cross-platform (Linux & Windows) Qt Application that uses glog for logging (commit: [`4d391fe`](https://github.com/google/glog/commit/4d391fe692ae6b9e0105f473945c415a3ce5a401)).  The project has a main application with several shared libraries that  we wrote.  On Linux (Ubuntu 14.04) glog works as expected.  On Windows  (built using mingw-w64 and gcc) any log statement that comes from within a DLL gets written to stdout instead of to the log.  Any log statement  from within the main application correctly gets written to the log.   Furthermore, I see `WARNING: Logging before InitGoogleLogging() is written to STDERR` in the standard output for each time a log statement is created from a  DLL for the first time (i.e. if I have 5 DLLs, I see that warning 5  times immediately prior to the first log statement from each DLL).
> 
> It seems like Glog is not being shared across the DLLs.  I have tried to call InitGoogleLogging from within each DLL to test this theory, but then I get a run time crash with the following error message in stdout:  `Check failed: !IsGoogleLoggingInitialized() You called InitGoogleLogging() twice!`.  So it appears that Glog is not being shared however, I can't initialize it in each DLL.

[Poco Logging with std::wstring or wchar_t](https://stackoverflow.com/questions/48945817/poco-logging-with-stdwstring-or-wchar-t)

[wchar_t support](https://github.com/baysao/google-glog/issues/4)

https://code.google.com/archive/p/google-glog/issues/4

[glog  print wchar_t?](https://github.com/google/glog/issues/64)

[Disable glog's "LOG(INFO)" logging](https://stackoverflow.com/questions/37397262/disable-glogs-loginfo-logging)
