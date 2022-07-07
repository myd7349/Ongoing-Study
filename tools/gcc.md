GCC for Windows:

- https://winlibs.com/
  
  - [GitHub - p-ranav/indicators: Activity Indicators for Modern C++](https://github.com/p-ranav/indicators#winlibs--mingw)

- Cygwin

- MinGW, Mingw-w64

- TDM-GCC

  - [Differences between Mingw-w64 and TDM-GCC for a simple GDI project](https://stackoverflow.com/questions/25538885/differences-between-mingw-w64-and-tdm-gcc-for-a-simple-gdi-project)

  - [What is the difference between Orwell's MinGW and TDM Dev-C++ versions?](https://stackoverflow.com/questions/21980774/what-is-the-difference-between-orwells-mingw-and-tdm-dev-c-versions/22185860)

[spdlog is packaged in such a way that including `<spdlog/spdlog.h>` gives a macro redefinition warning of the macro SPDLOG_FMT_EXTERNAL](https://github.com/Homebrew/homebrew-core/issues/88896)

> As for `-Werror`, I'm [not a fan](https://embeddedartistry.com/blog/2017/05/22/werror-is-not-your-friend/). But I know it's a common pattern.
