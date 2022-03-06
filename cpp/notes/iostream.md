https://github.com/mateidavid/zstr/blob/master/src/zstr.hpp

https://twitter.com/dEnergy_dTime/status/1465739946522726408

```c++
#include <iostream>
#include <iomanip>

int main() {
  std::cout.operator<<(std::endl<char, std::char_traits<char>>);
}
```

[When is it good to use c++ iostreams over ReadFile, WriteFile, fprintf, etc ...?](https://stackoverflow.com/questions/2111593/when-is-it-good-to-use-c-iostreams-over-readfile-writefile-fprintf-etc)

[A C++ Debug Stream for Win32](https://marknelson.us/posts/2001/09/01/win32-debug-stream.html)

sync_with_stdio

- https://en.cppreference.com/w/cpp/io/ios_base/sync_with_stdio
- https://en.cppreference.com/w/cpp/io/manip/endl

  > ```cpp
  > #include <iostream>
  > #include <chrono>
  > 
  > template<typename Diff>
  > void log_progress(Diff d)
  > {
  >    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(d).count()
  >               << " ms passed" << std::endl;
  > }
  >  
  > int main()
  > {
  >     std::cout.sync_with_stdio(false); // on some platforms, stdout flushes on \n
  >     volatile int sink = 0;
  >  
  >     auto t1 = std::chrono::high_resolution_clock::now();
  >     for (int j=0; j<5; ++j)
  >     {
  >         for (int n=0; n<10000; ++n)
  >             for (int m=0; m<20000; ++m)
  >                 sink += m*n; // do some work
  >         auto now = std::chrono::high_resolution_clock::now();
  >         log_progress(now - t1);
  >     }
  > }
  > ```
