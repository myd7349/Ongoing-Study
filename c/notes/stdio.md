1.

2018-08-16T09:34+08:00

https://stackoverflow.com/questions/44792526/differenence-among-open-open-and-fopen-with-regard-to-msvc-compiler

    For the Windows API, you can use _open_osfhandle() to create a FILE * from a HANDLE, and _get_osfhandle() to get the HANDLE from the FILE *. However, in both cases, the handle will be owned by the FILE *.
    
    For the POSIX API, you can use fdopen() to create a FILE * from a int file descriptor, and you can use fileno() to get the int file descriptor from a FILE *. Again, in both cases the file is owned by the FILE *.

2.

2019-05-24T18:41+08:00

stderr seems to be buffered on recent windows.

https://github.com/google/glog/blob/ba8a9f6952d04d1403b97df24e6836227751454e/src/logging_unittest.cc#L184

3.

https://github.com/google/glog/blob/ba8a9f6952d04d1403b97df24e6836227751454e/src/googletest.h

```c
// Return the size (in bytes) of a file
static inline size_t GetFileSize(FILE * file) {
  fseek(file, 0, SEEK_END);
  return static_cast<size_t>(ftell(file));
}
// Read the entire content of a file as a string
static inline string ReadEntireFile(FILE * file) {
  const size_t file_size = GetFileSize(file);
  char * const buffer = new char[file_size];

  size_t bytes_last_read = 0;  // # of bytes read in the last fread()
  size_t bytes_read = 0;       // # of bytes read so far

  fseek(file, 0, SEEK_SET);

  // Keep reading the file until we cannot read further or the
  // pre-determined file size is reached.
  do {
    bytes_last_read = fread(buffer+bytes_read, 1, file_size-bytes_read, file);
    bytes_read += bytes_last_read;
  } while (bytes_last_read > 0 && bytes_read < file_size);

  const string content = string(buffer, buffer+bytes_read);
  delete[] buffer;

  return content;
}
```

https://stackoverflow.com/questions/33327720/how-to-use-fread-to-read-the-entire-file-in-a-loop

> Note that this differs from the underlying read(2) POSIX system call. read() can return less than a full buffer if interrupted, or after a packet from a socket, or after a line on a line-buffered tty, and stuff like that. fread() keeps calling read until the buffer is full or it reaches EOF.

4.

https://github.com/google/glog/blob/ba8a9f6952d04d1403b97df24e6836227751454e/src/signalhandler.cc#L85-L86

The class is used for formatting error messages.  We don't use printf() as it's not async signal safe.

UNPv1 Ch5.9:

> 警告：在信号处理函数中调用诸如 printf 这样的标准 I/O 函数是不合适的，其原因将在 11.18 节讨论。
> https://stackoverflow.com/questions/25327519/how-to-send-udp-packet-every-1-ms

5.

Read a file line by line:

https://github.com/google/glog/blob/ba8a9f6952d04d1403b97df24e6836227751454e/src/symbolize.cc#L401-L444

UNPv1

6.

https://stackoverflow.com/questions/14543443/in-c-how-do-you-redirect-stdin-stdout-stderr-to-files-when-making-an-execvp-or

cpp/Google/glog/glog_src_playground/captured_stream.hpp

7.

2019-01-25T13:33+08:00

filecore.cpp

```c
ULONGLONG CStdioFile::GetLength() const
{
   ASSERT_VALID(this);

   LONG nCurrent;
   LONG nLength;
   LONG nResult;

   nCurrent = ftell(m_pStream);
   if (nCurrent == -1)
      AfxThrowFileException(CFileException::invalidFile, _doserrno,
         m_strFileName);

   nResult = fseek(m_pStream, 0, SEEK_END);
   if (nResult != 0)
      AfxThrowFileException(CFileException::badSeek, _doserrno,
         m_strFileName);

   nLength = ftell(m_pStream);
   if (nLength == -1)
      AfxThrowFileException(CFileException::invalidFile, _doserrno,
         m_strFileName);
   nResult = fseek(m_pStream, nCurrent, SEEK_SET);
   if (nResult != 0)
      AfxThrowFileException(CFileException::badSeek, _doserrno,
         m_strFileName);

   return nLength;
}
```

8. snprintf and vsnprintf

https://github.com/google/glog/blob/ba8a9f6952d04d1403b97df24e6836227751454e/src/windows/port.h#L118-L128

https://github.com/google/glog/blob/master/src/windows/port.cc

9. fopen for utf-8

https://github.com/ArtifexSoftware/mupdf/blob/b10c81f8d278534b277d181436d5b8e8a9723af9/source/fitz/time.c#L84-L108

10. fmemopen for Windows

https://github.com/NimbusKit/MemoryMapping

https://stackoverflow.com/questions/12249610/c-create-file-in-memory

https://stackoverflow.com/questions/7307955/is-there-fmemopen-in-mingw

https://github.com/kespindler/python-tesseract/blob/master/util-fmemopen.c

https://github.com/martinh/libconfuse/blob/master/src/fmemopen.c

https://sourceware.org/git/?p=glibc.git;a=blob;f=libio/fmemopen.c;h=c2c67c112063084bc1ef61a3e1ca59bebeeef087;hb=HEAD

https://github.com/njriasan/graphene-docker/blob/aa0a0dcc893a3865345c26a78299326cbc4c3e9c/graphene/LibOS/glibc-2.19/libio/fmemopen.c

https://sourcegraph.com/github.com/DanBloomberg/leptonica/-/blob/src/utils2.c#L1896:1-1896:20

11.

https://github.com/erikd/libsndfile/blob/master/src/file_io.c

https://github.com/GNOME/glib/blob/master/glib/gstdio.c

12.

https://github.com/jmcnamara/libxlsxwriter/commit/37656389c8a7dcd48a8fc7479f77c77519a73416

13.

[```fread``` returns number of objects read, not number of bytes](https://stackoverflow.com/questions/28398255/fread-return-value-in-c)

```c
// Ongoing-Study/cpp/OpenGL/opengl-tutorial/common/texture.cpp
unsigned char header[124];

if ((readBytes = fread(header, sizeof(header), 1, file)) != sizeof(header)) { // Oops!
  fprintf(stderr, "Unexpected DDS header size: %zu: ", readBytes);
  return 0;
}
```

14.

[c++: subprocess output to stdin](https://stackoverflow.com/questions/8438277/c-subprocess-output-to-stdin)

Internally, `popen(<command>)` is interpreted as:

> cmd /c <command>

If `<command>` contains spaces in it, quote the whole command just before passing it to `popen`.

[Creating a Child Process with Redirected Input and Output](https://docs.microsoft.com/en-us/windows/win32/procthread/creating-a-child-process-with-redirected-input-and-output)

[Using a handle to collect output from CreateProcess()](https://stackoverflow.com/questions/2674237/using-a-handle-to-collect-output-from-createprocess)

[launch an exe/process with stdin stdout and stderr?](https://stackoverflow.com/questions/5485923/launch-an-exe-process-with-stdin-stdout-and-stderr/39648986)

15.

[fgets to read line by line in files](https://stackoverflow.com/questions/21180248/fgets-to-read-line-by-line-in-files)

```c
    while (fgets(line, MAX_LINE_SIZE, fp) != NULL)
        ++col;
```

[fwrite vs stdout](https://stackoverflow.com/questions/17259250/fwrite-doesnt-print-anything-to-stdout)

```
char s[5] = { 'H', 'e', 'l', 'l', 'o' };
fwrite(s, 1, 5, stdout);
fflush(stdout);
```

https://github.com/microsoft/vcpkg/blob/f1bef4aa7ca7e2a6ea4f5dfe4850d95fce60b431/toolsrc/src/vcpkg/base/system.print.cpp#L8

16.

[C 语言中为什么没有直接提供二进制数的输出？](https://www.zhihu.com/question/438434182)

[Is there a printf converter to print in binary format?](https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format)

[Binary representation of a given number](https://www.geeksforgeeks.org/binary-representation-of-a-given-number/)

[Binary representation in C](https://stackoverflow.com/questions/8372646/binary-representation-in-c)

17.

[Create temporary file in C, MS Windows system](https://stackoverflow.com/questions/9717271/create-temporary-file-in-c-ms-windows-system)

18.

[C - create file in memory](https://stackoverflow.com/questions/12249610/c-create-file-in-memory)

https://github.com/libconfuse/libconfuse/blob/master/src/fmemopen.c

[Create temporary file in C, MS Windows system](https://stackoverflow.com/questions/9717271/create-temporary-file-in-c-ms-windows-system)

19.

[fopen](https://en.cppreference.com/w/cpp/io/c/fopen)

> File access mode flag `"b"` can optionally be specified to open a file [in binary mode](https://en.cppreference.com/w/cpp/io/c/FILE#Binary_and_text_modes). This flag has no effect on POSIX systems, but on Windows, for example, it disables special handling of '\n' and '\x1A'. 

[What does the \x1a characters mean](https://stackoverflow.com/questions/16255585/what-does-the-x1a-characters-mean)

> `\x1a` is a [SUB](http://en.wikipedia.org/wiki/Substitute_character) control character, used to mark end of a file (EOF).

20.

https://github.com/bbc/audiowaveform/blob/master/src/madlld-1.1p1/bstdfile.c

21. getline vs getdelim

https://en.cppreference.com/w/c/experimental/dynamic/getline

[Why does getline function works in K&R?](https://stackoverflow.com/questions/61160674/why-does-getline-function-works-in-kr)

[Where/how to get the "getline" function if it is missing from stdio.h?](https://stackoverflow.com/questions/27381903/where-how-to-get-the-getline-function-if-it-is-missing-from-stdio-h)

[Are there alternate implementations of GNU getline interface?](https://stackoverflow.com/questions/735126/are-there-alternate-implementations-of-gnu-getline-interface)

[C getline() implementation](https://codereview.stackexchange.com/questions/119219/c-getline-implementation)

https://github.com/lattera/glibc/blob/master/libio/iogetline.c

https://github.com/lattera/glibc/blob/master/stdio-common/getline.c

https://github.com/lattera/glibc/blob/master/libio/iogetdelim.c

https://github.com/bminor/glibc/blob/master/libio/iogetline.c

https://github.com/beejjorgensen/bgc/blob/main/src/bgc_part_0850_malloc.md#reading-in-lines-of-arbitrary-length

22. [how do I write to stdout from an MFC program?](https://stackoverflow.com/questions/5094502/how-do-i-write-to-stdout-from-an-mfc-program)

> ```c
> void EnablePrintfAtMFC()
> {
>  if (AttachConsole(ATTACH_PARENT_PROCESS))
>  {
>      FILE* pCout;
>      freopen_s(&pCout, "CONOUT$", "w", stdout);
>      std::cout.clear();
>      std::wcout.clear();
>  }
> }
> ```

23. https://github.com/Tencent/rapidjson/blob/master/example/prettyauto/prettyauto.cpp

> ```c
> // https://github.com/Tencent/rapidjson/blob/0d4517f15a8d7167ba9ae67f3f22a559ca841e3b/example/prettyauto/prettyauto.cpp#L19-L23
> #ifdef _WIN32
>     // Prevent Windows converting between CR+LF and LF
>     _setmode(_fileno(stdin), _O_BINARY);    // NEW
>     _setmode(_fileno(stdout), _O_BINARY);   // NEW
> #endif
> ```

24. [How can one print a size_t variable portably using the printf family?](https://stackoverflow.com/questions/2524611/how-can-one-print-a-size-t-variable-portably-using-the-printf-family)

> ```c
> size_t x = ...;
> ssize_t y = ...;
> printf("%zu\n", x);  // prints as unsigned decimal
> printf("%zx\n", x);  // prints as hex
> printf("%zd\n", y);  // prints as signed decimal
> ```

25. [Do progress reports/logging information belong on stderr or stdout?](https://unix.stackexchange.com/questions/331611/do-progress-reports-logging-information-belong-on-stderr-or-stdout)

> FWIW, in Python, `stdout` is line-buffered by default whereas `stderr` is unbuffered, so `stderr` is the natural choice for writing progress text / bars / spinners that don't contain a newline. (If you write such text on `stdout` you need to clutter up your progress output calls with `stdout.flush()` to make it visible).

https://git-scm.com/docs/git-bundle

> --quiet 
> 
> This flag makes the command not to report its progress on the standard error stream.

[C# progressbar update from c++ using managed c++ cli](https://stackoverflow.com/questions/37270112/c-sharp-progressbar-update-from-c-using-managed-c-cli)

26. [GitHub - MaJerle/lwprintf: Lightweight printf library optimized for embedded systems](https://github.com/MaJerle/lwprintf)

27. [wurlitzer.py](https://github.com/minrk/wurlitzer/blob/main/wurlitzer.py)

28. freopen
    
    - [PyStand/PyStand.cpp at 164a7b929d1d3c35f299da2669dc112775e724d7 · skywind3000/PyStand · GitHub](https://github.com/skywind3000/PyStand/blob/164a7b929d1d3c35f299da2669dc112775e724d7/PyStand.cpp#L324-L348)
    
    - [Rerouting stdin and stdout from C](https://stackoverflow.com/questions/584868/rerouting-stdin-and-stdout-from-c)
      
      > `freopen` is commonly misused, e.g. `stdin = freopen("newin", "r", stdin);`. This is no more portable than `fclose(stdin); stdin = fopen("newin", "r");`. Both expressions attempt to assign to `stdin`, which is not guaranteed to be assignable.
      > 
      > The right way to use `freopen` is to omit the assignment: `freopen("newin", "r", stdin);`
      
      > For those who wants to close standard descriptor before reopen it, there is a solution tested in msvc2015 UCRT, use sequence of `fclose`+`_close`+`freopen`: `const int stdin_fileno = _fileno(stdin); fclose(stdin); if (stdin_fileno < 0) _close(STDIN_FILENO); /* may reallocate console here */; freopen("CONIN$", "r", stdin); /* use _get_osfhandle + SetStdHandle for not console application */`. This has sence because `freopen` does not reuse already allocated descriptor and allocates a new one. So
      >  to force it to reuse the descriptor you have to close it first.
    
    - [win32 GUI app that writes usage text to stdout when invoked as "app.exe --help"](https://stackoverflow.com/questions/54536/win32-gui-app-that-writes-usage-text-to-stdout-when-invoked-as-app-exe-help)
      
      > ```c
      > // https://keep.imfreedom.org/pidgin/pidgin/file/tip/pidgin/win32/winpidgin.c
      > if (debug || help || version) {
      >     /* If stdout hasn't been redirected to a file, alloc a console
      >      *  (_istty() doesn't work for stuff using the GUI subsystem) */
      >     if (_fileno(stdout) == -1 || _fileno(stdout) == -2) {
      >         LPFNATTACHCONSOLE MyAttachConsole = NULL;
      >         if (hmod)
      >             MyAttachConsole = (LPFNATTACHCONSOLE)GetProcAddress(hmod, "AttachConsole");
      >         if ((MyAttachConsole && MyAttachConsole(ATTACH_PARENT_PROCESS)) || AllocConsole()) {
      >             freopen("CONOUT$", "w", stdout);
      >             freopen("CONOUT$", "w", stderr);
      >         }
      >     }
      > }
      > ```
      
      > ```c
      > if(AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()){
      >     freopen("CONOUT$", "w", stdout);
      >     freopen("CONOUT$", "w", stderr);
      > }
      > ```

29. [Unicode in Microsoft Windows - Wikipedia](https://en.wikipedia.org/wiki/Unicode_in_Microsoft_Windows#UTF-8)
    
    > Microsoft Windows has a code page designated for [UTF-8](https://en.wikipedia.org/wiki/UTF-8 "UTF-8"), code page 65001.[[9]](https://en.wikipedia.org/wiki/Unicode_in_Microsoft_Windows#cite_note-9) Prior to Windows 10 insider build 17035 (November 2017),[[10]](https://en.wikipedia.org/wiki/Unicode_in_Microsoft_Windows#cite_note-10) it was impossible to set the locale code page to 65001, leaving this 
    > code page only available for (a) explicit conversion functions such as 
    > MultiByteToWideChar and/or (b) the [Win32 console](https://en.wikipedia.org/wiki/Win32_console "Win32 console") command `chcp 65001` to translate stdin/out between UTF-8 and UTF-16. This means that "narrow" functions, in particular [fopen](https://en.wikipedia.org/wiki/C_file_input/output#fopen "C file input/output") (which opens files), cannot be called with UTF-8 strings, and in fact there is no way to open all possible files using `fopen` no matter what the locale is set to and/or what bytes are put in the 
    > string, as none of the available locales can produce all possible UTF-16
    >  characters. This problem also applies to all other APIs that take or 
    > return 8 bit strings, including Windows ones such as `SetWindowText`.
    > 
    > On all modern non-Windows platforms, the file-name string passed to `fopen` is effectively UTF-8. This produces an incompatibility between other 
    > platforms and Windows. The normal work-around is to add Windows-specific
    >  code to convert UTF-8 to UTF-16 using [MultiByteToWideChar](https://en.wikipedia.org/wiki/MultiByteToWideChar "MultiByteToWideChar") and call the "wide" function instead of `fopen`.[[11]](https://en.wikipedia.org/wiki/Unicode_in_Microsoft_Windows#cite_note-11) Another popular work-around is to convert the name to the [8.3 filename](https://en.wikipedia.org/wiki/8.3_filename "8.3 filename") equivalent, this is necessary if the `fopen` is inside a library function that takes a string filename and thus 
    > calling another function is not possible. There were also proposals to 
    > add new APIs to portable libraries such as [Boost](https://en.wikipedia.org/wiki/Boost_(C%2B%2B_libraries) "Boost (C++ libraries)") to do the necessary conversion, by adding new functions for opening and
    >  renaming files. These functions would pass filenames through unchanged 
    > on Unix, but translate them to UTF-16 on Windows. Such a library, 
    > Boost.Nowide,[[12]](https://en.wikipedia.org/wiki/Unicode_in_Microsoft_Windows#cite_note-12) was accepted into Boost[[13]](https://en.wikipedia.org/wiki/Unicode_in_Microsoft_Windows#cite_note-13) and will be part of the 1.73 release.[*[needs update](https://en.wikipedia.org/wiki/Wikipedia:Manual_of_Style/Dates_and_numbers#Chronological_items "Wikipedia:Manual of Style/Dates and numbers")*] This would allow code to be "portable", but required just as many code changes as calling the wide functions.
    > 
    > In April 2018, with insider build 17035 (nominal build 17134) for
    >  Windows 10, a "Beta: Use Unicode UTF-8 for worldwide language support" 
    > checkbox appeared for setting the locale code page to UTF-8.[[a]](https://en.wikipedia.org/wiki/Unicode_in_Microsoft_Windows#cite_note-14) This allows for calling "narrow" functions, including `fopen` and `SetWindowTextA`, with UTF-8 strings. In May 2019 Microsoft added the ability for a program to set the code page to UTF-8 itself.[[14]](https://en.wikipedia.org/wiki/Unicode_in_Microsoft_Windows#cite_note-Microsoft-UTF-8-15)

30. [Printf width specifier to maintain precision of floating-point value](https://stackoverflow.com/questions/16839658/printf-width-specifier-to-maintain-precision-of-floating-point-value)
    
    > ```c
    > #include <float.h>
    > int Digs = DECIMAL_DIG;
    > double OneSeventh = 1.0/7.0;
    > printf("%.*e\n", Digs, OneSeventh);
    > // 1.428571428571428492127e-01
    > ```

31. [Why in msvc++ we have _snprintf while other compilers allows snprintf](https://stackoverflow.com/questions/11579095/why-in-msvc-we-have-snprintf-while-other-compilers-allows-snprintf)
    
    > Identifiers in the global namespace starting with _ are reserved for the implementation. _snprintf is just a function that the implementation (Visual Studio) has provided. As to the rationale for that, Visual Studio implements C89, and snprintf is part of a later C99 standard. 

32. tmpnam vs tempnam
- https://en.cppreference.com/w/cpp/io/c/tmpnam
- [tempnam() — Generate a temporary file name](https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-tempnam-generate-temporary-file-name)
  > ```c 
  > #define _XOPEN_SOURCE
  > #include <stdio.h>
  >
  > char *tempnam(const char *dir, const char *pfx);
  > ```
  > 
  > The tempnam() function generates a path name that may be used for a temporary file. If the environment variable TMPDIR is set, then the directory it specifies will be used as the directory part of the generated path name if it is accessible. Otherwise, if the dir argument is non-NULL and accessible, it will be used in the generated path name. Otherwise, the value of {P_tmpdir} defined in the <stdio.h> header is used as the directory component of the name. If that is inaccessible, then /tmp is used.
- https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/tempnam-wtempnam-tmpnam-wtmpnam?view=msvc-170
  > tmpnam returns a name that's unique in the designated Windows temporary directory returned by GetTempPathW. _tempnam generates a unique name in a directory other than the designated one.

33. scanf
- [How to prevent scanf causing a buffer overflow in C?](https://stackoverflow.com/questions/1621394/how-to-prevent-scanf-causing-a-buffer-overflow-in-c)
- [How to do string buffter overflow with scanf function?](https://security.stackexchange.com/questions/244249/how-to-do-string-buffter-overflow-with-scanf-function)

34. freopen

[How to restore stdout after using freopen](https://stackoverflow.com/questions/5846691/how-to-restore-stdout-after-using-freopen)

```c
fclose(stdout);
stdout = fdopen(1, "w"); //reopen: 1 is file descriptor of std output
```

[STDIN_FILENO undeclared in Windows](https://stackoverflow.com/questions/13531677/stdin-fileno-undeclared-in-windows)

[How to redirect the output back to the screen after freopen("out.txt", "a", stdout)](https://stackoverflow.com/questions/1908687/how-to-redirect-the-output-back-to-the-screen-after-freopenout-txt-a-stdo)

```c
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#define fdopen _fdopen
#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#else
#include <unistd.h>
#endif

int main(void)
{
    int a, b;

    if (freopen("./input.txt", "r", stdin) == NULL)
    {
        perror("freopen(stdin) failed");
        return EXIT_FAILURE;
    }

    scanf("%d %d", &a, &b);
	fclose(stdin);

    if (freopen("./output.txt", "w", stdout) == NULL)
    {
        perror("freopen(stdout) failed");
        return EXIT_FAILURE;
    }

    printf("sum(%d, %d) == %d\n", a, b, a + b);
	fclose(stdout);

    stdin = fdopen(STDIN_FILENO, "r");
	stdout = fdopen(STDOUT_FILENO, "w");

	return 0;
}
```

```c
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
//#define fdopen _fdopen
//#define STDIN_FILENO 0
//#define STDOUT_FILENO 1
#else
#include <unistd.h>
#endif


void sum_test(void)
{
	int a, b;
	scanf("%d %d", &a, &b);
	printf("sum(%d, %d) == %d\n", a, b, a + b);
}


int main(void)
{
    if (freopen("./input.txt", "r", stdin) == NULL)
    {
        perror("freopen(stdin) failed");
        return EXIT_FAILURE;
    }

    if (freopen("./output.txt", "w", stdout) == NULL)
    {
        perror("freopen(stdout) failed");
        return EXIT_FAILURE;
    }

    sum_test();

    fclose(stdin);
	fclose(stdout);

#ifdef _WIN32
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
#else
	// freopen ("/dev/tty", "a", stdout)
    stdin = fdopen(STDIN_FILENO, "r");
	stdout = fdopen(STDOUT_FILENO, "w");
#endif

    sum_test();

	return 0;
}
```

```cpp
#include <cstdio>
#include <cstdlib>
#include <iostream>


void sum_test()
{
	int a, b;
	std::scanf("%d %d", &a, &b);
	std::printf("C: sum(%d, %d) == %d\n", a, b, a + b);
}

void sum_test_cpp()
{
	int a, b;
	std::cin >> a >> b;
	std::cout << "C++: sum(" << a << ", " << b << ") == " << a + b << std::endl; 
}


int main(void)
{
	std::ios::sync_with_stdio(false);

    if (std::freopen("./input.txt", "r", stdin) == NULL)
    {
        std::perror("freopen(stdin) failed");
        return EXIT_FAILURE;
    }

    if (std::freopen("./output.txt", "w+", stdout) == NULL)
    {
        std::perror("freopen(stdout) failed");
        return EXIT_FAILURE;
    }

    sum_test();
	sum_test_cpp();

    std::fclose(stdin);
	std::fclose(stdout);

	return 0;
}

// https://stackoverflow.com/questions/65068411/question-about-using-freopen-and-cin-cout-to-read-large-input-from-file
// http://c-faq.com/stdio/undofreopen.html
```

35. feof

[don't use feof](https://gitlab.freedesktop.org/uchardet/uchardet/-/merge_requests/12)

[Why it's bad to use feof() to control a loop](https://faq.cprogramming.com/cgi-bin/smartfaq.cgi?answer=1046476070&id=1043284351)

36. ftello

https://www.teuniz.net/edf/index.html

https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-ftello-get-current-file-position

```c
#define _XOPEN_SOURCE 500
#include <stdio.h>

off_t ftello(FILE *stream);

#define _OPEN_SYS_UNLOCKED_EXT 1
#include <stdio.h>

off_t ftello_unlocked(FILE *stream);
```

37. fseeko

https://gitlab.com/Teuniz/EDFbrowser/-/blob/master/cnvs/nk2edf.cpp

38.

https://github.com/microsoft/vcpkg-tool/blob/main/src/tls12-download.c

```c
static void set_delete_on_close_flag(const HANDLE std_out, const HANDLE target, BOOL setting)
{
    FILE_DISPOSITION_INFO fdi = {0};
    fdi.DeleteFile = setting;
    if (SetFileInformationByHandle(target, FileDispositionInfo, &fdi, sizeof(fdi)) == 0)
    {
        abort_api_failure(std_out, L"SetFileInformationByHandle");
    }
}
```
