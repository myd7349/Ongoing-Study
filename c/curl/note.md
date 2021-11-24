### 1. How to build libcurl with VS2010?

[Visual Studio(VS2017/VS2019)编译并配置C/C++-libcurl开发环境](https://blog.csdn.net/DaSo_CSDN/article/details/77587916)

[vs2017---vs2010 如何编译和使用libcurl库](https://blog.csdn.net/cym1990/article/details/79851039)

Please read [`curl/winbuild/README.md`](https://github.com/curl/curl/blob/master/winbuild/README.md) first. Then:

> ```
> cd curl
> ./buildconf.bat
> cd winbuild
> nmake /f Makefile.vc mode=dll VC=10 MACHINE=x86 DEBUG=yes
> nmake /f Makefile.vc mode=static VC=10 MACHINE=x86 DEBUG=no
> nmake /f Makefile.vc mode=static VC=14 RTLIBCFG=static
> ```

[VS2015编译适用于XP系统sp3的dll全过程-无需vs2015运行库](https://www.pianshen.com/article/1160274201/)

[VS2015编译 libcurl 适用于Windows XP sp3 的DLL(无需VS2015运行库)](http://www.plsql.cc/archives/vs2015编译libcurl适用于windowsxpsp3的dll无需vs2015运行库)

[Unresolved external symbol - IdnToAscii](https://stackoverflow.com/questions/12530947/unresolved-external-symbol-idntoascii)

[How to remove dependency of normaliz.dll in libcurl?](https://stackoverflow.com/questions/47919466/how-to-remove-dependency-of-normaliz-dll-in-libcurl)

[VS2005 编译libcurl 报Normaliz.lib缺失的解决](https://blog.csdn.net/tonyfield2015/article/details/105744083)

[解决libcurl7.50.3在windows  XP SP3 VC++ 6.0下编译报错 unresolved external symbol __imp__IdnToAscii@20  unresolved external symbol __imp__IdnToUnicode@20](https://www.cnblogs.com/passedbylove/p/5979927.html)

[problem with normaliz.dll](https://social.msdn.microsoft.com/Forums/en-US/b5ad1d13-fa85-47cc-a79c-1ea81229b46c/problem-with-normalizdll?forum=devdocs)

http://www.dll-files.com/dllindex/dll-files.shtml?normaliz

https://github.com/curl/curl-for-win
