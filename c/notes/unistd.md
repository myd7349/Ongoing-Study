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

getopt

- [getopt - Command line option parsing](http://pymotw.com/2/getopt/)

- [`getopt`](https://docs.python.org/3/library/getopt.html#module-getopt) — C-style parser for command line

- [Linux下getopt()函数的简单使用](https://www.cnblogs.com/qingergege/p/5914218.html)

- [原来命令行参数处理可以这么写-getopt？](http://blog.csdn.net/huangxiaohu_coder/article/details/7475156)

- [getopt C++ example](https://gist.github.com/avances123/2406651)

- [Using getopt() in C++ to handle arguments](https://stackoverflow.com/questions/52467531/using-getopt-in-c-to-handle-arguments)

- https://github.com/gnif/LookingGlass/blob/c0c63fd93bf999b6601a782fec8b56e9133388cc/client/main.c#L1391

- [Example of getopt](https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html)

- [Mead's Guide to getopt](https://azrael.digipen.edu/~mmead/www/Courses/CS180/getopt.html)

- https://github.com/cnr-isti-vclab/vcglib/blob/master/wrap/system/qgetopt.h

  and a C++(Qt) wrapper:

  https://github.com/cnr-isti-vclab/vcglib/blob/master/wrap/system/qgetopt.h
  
- https://github.com/wolfpld/tracy/blob/master/capture/src/capture.cpp

- [getopt_long() -- proper way to use it?](https://stackoverflow.com/questions/7489093/getopt-long-proper-way-to-use-it)

- [Where does getopt_long store an unrecognized option?](https://stackoverflow.com/questions/2723888/where-does-getopt-long-store-an-unrecognized-option)

- [Why does C getopt_long_only() not set optopt for unknown option?](https://stackoverflow.com/questions/53828309/why-does-c-getopt-long-only-not-set-optopt-for-unknown-option)

  > `optopt` is indeed set to zero when unknown long option is found, see [here](https://github.com/lattera/glibc/blob/master/posix/getopt.c#L302).
  
  [getopt_long](https://docs.oracle.com/cd/E86824_01/html/E54766/getopt-long-3c.html)
  
  > If the first character of the `shortopts` argument (after a potential plus or minus character) is a colon (:), a colon is returned by `getopt_long()` in response to a missing argument; otherwise, a question mark (?) is returned for this condition.
  
  Code snippet 1:
  
  ```c
  struct option options[] =
  {
      { "input", required_argument, NULL, 'i' },
      { "help", no_argument, NULL, 'h' },
      { "version", no_argument, NULL, 'v' },
      { NULL, 0, NULL, 0 }
  };
  
  int result;
  int index = -1;
  
  while ((result = getopt_long(argc, argv, "hv", options, &index)) != -1)
  {
      switch (result)
      {
          case 0:
              break;
          case 'i':
              break;
          case 'h':
              break;
          case 'v':
              break;
          case '?':
              if (optopt == 0)
                  printf("Unkonwn option \"%s\".\n", argv[optind - 1]);
              else
                  printf("Missing argument for option \"%s\".\n", argv[optind - 1]);
              break;
          default:
              break;
      }
      
      index = -1;
  }
  ```
  
  Code snippet 2:
  
  ```c
  struct option options[] =
  {
      { "input", required_argument, NULL, 'i' },
      { "help", no_argument, NULL, 'h' },
      { "version", no_argument, NULL, 'v' },
      { NULL, 0, NULL, 0 }
  };
  
  int result;
  int index = -1;
  
  while ((result = getopt_long(argc, argv, ":hv", options, &index)) != -1)
  {
      switch (result)
      {
          case 0:
              break;
          case 'i':
              break;
          case 'h':
              break;
          case 'v':
              break;
          case '?':
              printf("Unkonwn option \"%s\".\n", argv[optind - 1]);
              break;
          case ':':
              printf("Missing argument for option \"%s\".\n", argv[optind - 1]);
              break;
          default:
              break;
      }
      
      index = -1;
  }
  
  // TODO:
  // Test with command line:
  // -i
  // -i in.txt
  // -a
  // -abc
  ```
  
- [getopt_long() option with optional argument](https://stackoverflow.com/questions/40594208/getopt-long-option-with-optional-argument)

- [getopt_long does not parse optional arguments to parameters](https://stackoverflow.com/questions/1052746/getopt-does-not-parse-optional-arguments-to-parameters)

- [getopt_long don't return 0 when have flag set in struct option](https://stackoverflow.com/questions/16852260/getopt-long-dont-return-0-when-have-flag-set-in-struct-option)

- [Understanding `option long_options[\]` when using `getopt_long`](https://stackoverflow.com/questions/39966025/understanding-option-long-options-when-using-getopt-long)

- [Getopt - adding case for both missing option and missing non-option argument](https://stackoverflow.com/questions/36900389/getopt-adding-case-for-both-missing-option-and-missing-non-option-argument)

- [Using getopt in C with non-option arguments](https://stackoverflow.com/questions/18079340/using-getopt-in-c-with-non-option-arguments)

- https://github.com/nihui/waifu2x-ncnn-vulkan/blob/master/src/main.cpp

  > ```c
  > #if _WIN32
  > #include <wchar.h>
  > static wchar_t* optarg = NULL;
  > static int optind = 1;
  > static wchar_t getopt(int argc, wchar_t* const argv[], const wchar_t* optstring)
  > {
  >     if (optind >= argc || argv[optind][0] != L'-')
  >         return -1;
  > 
  >     wchar_t opt = argv[optind][1];
  >     const wchar_t* p = wcschr(optstring, opt);
  >     if (p == NULL)
  >         return L'?';
  > 
  >     optarg = NULL;
  > 
  >     if (p[1] == L':')
  >     {
  >         optind++;
  >         if (optind >= argc)
  >             return L'?';
  > 
  >         optarg = argv[optind];
  >     }
  > 
  >     optind++;
  > 
  >     return opt;
  > }
  > #endif
  > ```

  

