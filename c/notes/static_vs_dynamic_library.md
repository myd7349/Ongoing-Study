[Can a C++ Static Library link to shared library?](https://stackoverflow.com/questions/1242820/can-a-c-static-library-link-to-shared-library)

[Can I mix static and shared-object libraries when linking?](https://stackoverflow.com/questions/2954387/can-i-mix-static-and-shared-object-libraries-when-linking)

```
/home/runner/work/WavelibTest/WavelibTest/wavelib-test/build
/home/runner/work/WavelibTest/WavelibTest
-- The C compiler identification is GNU 7.5.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc - works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/runner/work/WavelibTest/WavelibTest/wavelib-test/build
Scanning dependencies of target remove_baseline_drift
[ 25%] Building C object CMakeFiles/remove_baseline_drift.dir/remove_baseline_drift.c.o
[ 50%] Linking C shared library libremove_baseline_drift.so
/usr/bin/ld: /home/runner/work/WavelibTest/WavelibTest/wavelib/build/install/lib/libwavelib.a(wavelib.c.o): relocation R_X86_64_PC32 against symbol `imodwt_fft' can not be used when making a shared object; recompile with -fPIC
/usr/bin/ld: final link failed: Bad value
collect2: error: ld returned 1 exit status
make[3]: *** [libremove_baseline_drift.so] Error 1
CMakeFiles/remove_baseline_drift.dir/build.make:101: recipe for target 'libremove_baseline_drift.so' failed
make[2]: *** [CMakeFiles/remove_baseline_drift.dir/all] Error 2
CMakeFiles/Makefile2:121: recipe for target 'CMakeFiles/remove_baseline_drift.dir/all' failed
make[1]: *** [CMakeFiles/WavelibTest.dir/rule] Error 2
CMakeFiles/Makefile2:101: recipe for target 'CMakeFiles/WavelibTest.dir/rule' failed
make: *** [WavelibTest] Error 2
Makefile:135: recipe for target 'WavelibTest' failed
##[error]Process completed with exit code 2.
```

[Convert a Static Library to a Shared Library?](https://stackoverflow.com/questions/655163/convert-a-static-library-to-a-shared-library)

[Linking to a .dll file without the .lib](https://stackoverflow.com/questions/45030749/linking-to-a-dll-file-without-the-lib)

[Static library debug symbols](https://stackoverflow.com/questions/7575298/static-library-debug-symbols)

[cross_compiler_call](https://github.com/jbandela/cross_compiler_call)

[Technically, how do variadic functions work? How does printf work?](https://stackoverflow.com/questions/23104628/technically-how-do-variadic-functions-work-how-does-printf-work)

How to load a dll from memory?

- [MemoryModule](https://github.com/fancycode/MemoryModule)

- [pupy/LoadLibraryR.c at unstable · n1nj4sec/pupy · GitHub](https://github.com/n1nj4sec/pupy/blob/unstable/client/sources/LoadLibraryR.c)

- [py2exe/MemoryModule.c at master · py2exe/py2exe · GitHub](https://github.com/py2exe/py2exe/blob/master/source/MemoryModule.c)

[What is the use of .exp and what is the difference between .lib and .dll?](https://stackoverflow.com/questions/2727020/what-is-the-use-of-exp-and-what-is-the-difference-between-lib-and-dll)

fftw-3.3.5-dll32\README-WINDOWS

> In order to link to these .dll files from Visual C++, you need to create .lib "import libraries" for them, and can do so with the "lib" command that comes with VC++.  In particular, run:
> 
>   lib /def:libfftw3f-3.def
>   
>   lib /def:libfftw3-3.def
>   
>   lib /def:libfftw3l-3.def

[What's the format of .lib in windows?](https://stackoverflow.com/questions/3811437/whats-the-format-of-lib-in-windows)
