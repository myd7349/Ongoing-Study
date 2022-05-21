[MSVCRT: Where is the implement (source code) of sin, cos et al?](https://stackoverflow.com/questions/7621089/msvcrt-where-is-the-implement-source-code-of-sin-cos-et-al)
> C:\WINDOWS\WinSxS\x86_Microsoft.VC90.CRT_...>dumpbin /exports msvcr90.dll | findstr sin

[Wumpbin](https://www.benf.org/other/wumpbin/index.html)

[How to check for DLL dependency?](https://stackoverflow.com/questions/7378959/how-to-check-for-dll-dependency)

[How did you get libclang.dll and libLLVM.dll](https://github.com/dotnet/ClangSharp/issues/3)

> I see at LLVMSharp that you have a nice script to generate libclang.dll and libLLVM.dll by first putting related libs into a library, running dumpbin to get the defined symbols, filtering for only the symbols you're interested in, placing them into a DEF file, and then linking the library to produce a dll.
