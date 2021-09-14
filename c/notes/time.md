1. mktime

https://github.com/protocolbuffers/protobuf/blob/77f03d932a35e8aa0a98c0c728ad3f5aacfe30ce/php/ext/google/protobuf/upb.c#L10490

MFC CTime

Note that:

CTime can not supports date time that is earlier than 1970-01-01 00:00:00, but COleDateTime can. 

2. Wall-clock time

>Class std::chrono::steady_clock represents a monotonic clock. The time points of this clock cannot decrease as physical time moves forward. This clock is not related to wall clock time (for example, it can be time since last reboot), and is most suitable for measuring intervals.

https://en.wikipedia.org/wiki/Wall-clock_time

https://stackoverflow.com/questions/7335920/what-specifically-are-wall-clock-time-user-cpu-time-and-system-cpu-time-in-uni

3. [How do I construct an ISO 8601 datetime in C++?](https://stackoverflow.com/questions/9527960/how-do-i-construct-an-iso-8601-datetime-in-c)

> ```c
> #include <ctime>
> #include <iostream>
> 
> int main() {
>     time_t now;
>     time(&now);
>     char buf[sizeof "2011-10-08T07:07:09Z"];
>     strftime(buf, sizeof buf, "%FT%TZ", gmtime(&now));
>     // this will work too, if your compiler doesn't support %F or %T:
>     //strftime(buf, sizeof buf, "%Y-%m-%dT%H:%M:%SZ", gmtime(&now));
>     std::cout << buf << "\n";
> }
> ```

and another example:

> ```c
> #include <ctime>
> #include <chrono>
> #include <iostream> 
> #include <locale>  
> 
> #if defined (_WIN32) 
> #define WINDOWSLIB 1
> #elif defined (__APPLE__)//iOS, Mac OS
> #define MACOSLIB 1
> #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__) || defined(__linux) || defined(linux)//_Ubuntu - Fedora - Centos - RedHat
> #define LINUXLIB 1
> #elif defined (__EMSCRIPTEN__)
> #define EMSCRIPTENLIB 1
> #endif
> 
> #define WriteLine(data)std::cout<< data <<std::endl;
> typedef std::string String;
> 
> String CurrentISO8601DateTime(bool toUTC=true)
> {
>     using namespace std::chrono;
>     system_clock::time_point now = system_clock::now();
>     time_t timet = system_clock::to_time_t(now);
>     std::tm tm{};
>     String localeStr = setlocale(LC_ALL, nullptr);
>     setlocale(LC_ALL, u8"");
>     String format = String(u8"%FT%T.").append(std::to_string(duration_cast<milliseconds>(now.time_since_epoch()).count() % static_cast<long long>(1000)));
>     if (toUTC)
>     {
> #ifdef WINDOWSLIB
>         gmtime_s(&tm, &timet);
> #elif LINUXLIB
>         gmtime_r(&timet, &tm);
> #elif EMSCRIPTENLIB
>         gmtime_r(&timet, &tm);
> #endif
>         format = format.append(u8"Z");
>     }
>     else
>     {
> #ifdef WINDOWSLIB
>         localtime_s(&tm, &timet);
> #elif LINUXLIB
>         localtime_r(&timet, &tm);
> #elif EMSCRIPTENLIB
>         localtime_r(&timet, &tm);
> #endif
>         format.append(u8"%z");
>     }
>     String result = String(255, 0);
>     const size_t length = std::strftime(&result[0], result.size(), format.c_str(), &tm);
>     result.resize(length);
>     setlocale(LC_ALL, localeStr.c_str());
>     return result;
> }
> 
> #define ConsoleWriteLn(data) std::cout<< data <<std::endl;
> 
> int main()
> {
>     ConsoleWriteLn(u8"UTC  : " + CurrentISO8601DateTime());
>     ConsoleWriteLn(u8"LOCAL: " + CurrentISO8601DateTime(false));
> }
> ```

3. strptime

- [Is there an available and licensed version of strptime.h that will compile in Visual Studio?](https://stackoverflow.com/questions/11688565/is-there-an-available-and-licensed-version-of-strptime-h-that-will-compile-in-vi)
  - https://github.com/UC-c0de/googlesitemapgenerator/blob/master/src/common/timesupport.cc
- http://cvsweb.netbsd.org/bsdweb.cgi/src/lib/libc/time/strptime.c?rev=HEAD
- [Parsing date/time strings problem](https://stackoverflow.com/questions/4325847/parsing-date-time-strings-problem)

